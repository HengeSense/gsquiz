<?php

/**
 * @file
 * Custom field used to display applications in any entities.
 */

/**
 * Defines predicate prefix which is used with the relation module.
 * http://drupal.org/project/relation
 */
define("RECRUIT_APPLICATION_REFERENCE_PREDICATE_PREFIX", "recruit_application_reference_");

/**
 * Implementation of hook_field_info().
 */
function recruit_application_field_info() {
  return array(
    'recruit_application_reference' => array(
      'label' => t('Application reference'),
      'description' => t('Attach applications to any content types'),
      'default_widget' => 'recruit_application_reference_select_list',
      'default_formatter' => 'recruit_application_reference_link',
    ),
  );
}

/**
 * Implements hook_field_widget_info().
 */
function recruit_application_field_widget_info() {
  return array(
    'recruit_application_reference_select_list' => array(
      'label' => t('Select list'),
      'field types' => array('recruit_application_reference'),
    ),
  );
}

/**
 * Implements hook_field_formatter_info().
 */
function recruit_application_field_formatter_info() {
  return array(
    //'recruit_application_reference_application_form' => array(
    //  'label' => t('Application form'),
    //  'description' => t('Display the application form.'),
    // 'field types' => array('recruit_application_reference'),
    //),
    'recruit_application_reference_link' => array(
      'label' => t('Link'),
      'description' => t('Links to an application form on a separate form.'),
      'field types' => array('recruit_application_reference'),
      'settings' =>  array(
        'link_label' => 'Apply',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function recruit_application_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $form = array();

  if ($display['type'] == 'recruit_application_reference_link') {
    $form['link_label'] = array(
      '#type' => 'textfield',
      '#title' => t('Link label'),
      '#default_value' => $settings['link_label'],
      '#required' => TRUE,
    );
  }

  return $form;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function recruit_application_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $summary = '';

  if ($display['type'] == 'recruit_application_reference_link') {
    $summary = t('Link label:') . ' ' . $settings['link_label'];
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_view().
 */
function recruit_application_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $result = array();
  switch ($display['type']) {
    case 'recruit_application_reference_application_form':

      foreach ($items as $delta => $item) {
        $result[$delta] = array(
          '#markup' => render(drupal_get_form('recruit_application_reference_application_form', recruit_application_new($item['application_type']))),
        );
      }

      break;
    case 'recruit_application_reference_link':
      foreach ($items as $delta => $item) {

        //Get entity uri.
        $entity_ids = entity_extract_ids($entity_type, $entity);
        $url_query = array('et' => $entity_type, 'id' => $entity_ids[0]);
        //Get link label setting.
        $link_label = $display['settings']['link_label'];
        $result[$delta] = array(
          '#markup' => l(check_plain($link_label), 'recruit-application/' . strtr($item['application_type'], array('_' => '-')) . '/apply', array('query' => $url_query)),
        );
      }
      break;

  }
  return $result;
}

/**
 * Implementation of hook_field_is_empty().
 */
function recruit_application_field_is_empty($item, $field) {

  if ($field['type'] == 'recruit_application_reference') {

    if (empty($item['application_type'])) {
     return TRUE;
    }

  }

  return FALSE;
}

/**
 * Implementation of hook_field_settings_form().
 */
function recruit_application_field_settings_form($field, $instance, $has_data) {
  if ($field['type'] == 'recruit_application_reference') {

  }
}

/**
 * Implementation of hook_field_validate().
 */
function recruit_application_field_validate($obj_type, $object, $field, $instance, $langcode, &$items, &$errors) {
  if ($field['type'] == 'recruit_application_reference') {

  }
}

/**
 * Implements hook_field_widget_settings_form().
 */
function recruit_application_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $defaults = field_info_widget_settings($widget['type']);
  $settings = array_merge($defaults, $widget['settings']);

  $form = array();

  if ($widget['type'] == 'recruit_application_reference_select_list') {

  }

  return $form;
}

/**
 * Implementation of hook_field_widget_form().
 */
function recruit_application_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $base = $element;
  if ($instance['widget']['type'] == 'recruit_application_reference_select_list') {
    $widget = $instance['widget'];
    $settings = $widget['settings'];

    // Build an options array of the application types.
    foreach (recruit_application_get_types() as $type => $name) {
      $options[$type] = check_plain($name->label);
    }

    $element['application_type'] = array(
      '#type' => 'select',
      '#title' => t('Which application form should be used?'),
      '#options' => $options,
      '#default_value' => isset($items[$delta]['application_type']) ? $items[$delta]['application_type'] : NULL,
    );
  }

  return $element;
}

/**
 * Helper function used to return field type.
 */
function _recruit_application_get_field_type($field_name) {
  // Get field info.
  $field = field_info_field($field_name);

  // If field exists return type.
  if (!empty($field)) {
    return $field['type'];
  }
}

/**
 * Helper function used to return the full predicate name.
 */
function _recruit_application_create_predicate_name($entity_type) {
  return RECRUIT_APPLICATION_REFERENCE_PREDICATE_PREFIX . $entity_type;
}

/**
 * Helper function used to create entity relations for application reference fields.
 */
function _recruit_application_create_relation_type($entity_type) {
  // Create source bundles.
  $source_bundles = array(
    'recruit_application:*' => 'recruit_application:*',
    $entity_type . ':*' => $entity_type . ':*',
  );

  // Build record array.
  $record = array(
    'predicate'   => _recruit_application_create_predicate_name($entity_type),
    'min_arity'   => 2,
    'max_arity'   => 2,
    'label' => t('Applications for (!entity_type)', array('!entity_type' => $entity_type)),
    'directional' => 0,
    'transitive' => 0,
    'source_bundles' => $source_bundles,
    'target_bundles' => array(),
  );

  // Save relation type.
  relation_type_save($record, array());
}

/**
 * Helper function used to create entity relationships which applications and jobs.
 */
function _recruit_application_create_relation($entity_type, $entity_id, $aid) {
  $entity_keys = array();

  $entity_keys[] = array(
    'entity_type' => 'recruit_application',
    'entity_id' => $aid,
  );

  $entity_keys[] = array(
    'entity_type' => $entity_type,
    'entity_id' => $entity_id,
  );

  $predicate = _recruit_application_create_predicate_name($entity_type);

  relation_create($predicate, $entity_keys);
}

/**
 * Implements hook_field_create_instance().
 *
 * Create relation when application reference instance get's created.
 */
function recruit_application_field_create_instance($instance) {
  // Only create relation for recruit_application_reference field.
  if (_recruit_application_get_field_type($instance['field_name']) == 'recruit_application_reference' && $instance['entity_type'] != 'recruit_application') {
    // Load defined predicate.
    $predicate = relation_type_load(_recruit_application_create_predicate_name($instance['entity_type']));
    // If predicate has not already been created.
    if (empty($predicate)) {
      // Create relation.
      _recruit_application_create_relation_type($instance['entity_type']);
    }
  }
}