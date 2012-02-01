<?php

/**
 * @file
 * Contains the basic application full name field.
 */

/**
 * Field handler to present a applications's operations links.
 */
class recruit_application_handler_field_application_relation extends recruit_application_handler_field_application {
  function construct() {
    parent::construct();

    $this->additional_fields['aid'] = 'aid';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $aid = $values->{$this->aliases['aid']};
    $entity_id = $aid;
    $entity_type = 'recruit_application';
    $items = $this->_get_relation($aid);
    
      foreach ($items as $delta => $item) {
        
        $links = array();
        foreach ($item->endpoints[LANGUAGE_NONE] as $endpoint) {
          $related_entities = entity_load($endpoint['entity_type'], array($endpoint['entity_id']));
          $related_entity = reset($related_entities);
          $link = array();
          if ($endpoint['entity_type'] != $entity_type && $endpoint['entity_id'] != $entity_id) {
            $link = entity_uri($endpoint['entity_type'], $related_entity);
            $link['href'] = $link['path'];
            $link['title'] = entity_label($endpoint['entity_type'], $related_entity);
          }
          if (!empty($link)) {
            $links[] = $link;
          }
        }
      }
      
      // If relation is return, then link to the "job" entity.
      if (count($links) == 1) {
        return l(check_plain($links[0]['title']), $links[0]['path']);
      }
  }

  /*
   * Private method used to get relation entites by application ID.
   */
  function _get_relation($aid) {
    $relation_ids = array_keys(relation_query('recruit_application', $aid)->execute());
    return $relation_ids ? array_values(entity_load('relation', $relation_ids)) : array();
  }
  
}
