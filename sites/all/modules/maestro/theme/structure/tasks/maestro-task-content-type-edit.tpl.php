<?php
// $Id:

/**
 * @file
 * maestro-task-content-type-edit.tpl.php
 */

?>
<br></br>
<table>
  <tr>
    <td>
      <?php print t('Select the Content Type for this task:'); ?>
      <select name="content_type">
        <?php foreach($content_types as $type => $obj) {?>
        <option value="<?php print $obj->type; ?>" <?php if($obj->type == $td_rec->task_data['content_type']) print "selected"; ?>>
          <?php print $obj->name; ?>
        </option>
        <?php } ?>
      </select>
    </td>
  </tr>
  <?php
  if (module_exists('prepopulate')):
  ?>
  <tr>
    <td>
      <?php print t('Fill rules for node form:'); ?><br />
      <textarea name="fill_rules"><?php print $td_rec->task_data['fill_rules']; ?></textarea>
      <div class="description">Use the syntax of prepopulate module, like edit[title]=moo , where moo is a maestro variable name. The title field in this case is filled by the actual value of the moo variable.</div>
    </td>
  </tr>
  <?php
  endif;
  ?>
</table>
