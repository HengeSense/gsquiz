<?php

/**
 * @file
 * Default theme implementation to present the title on a job page.
 *
 * Available variables:
 * - $title: The title to render.
 * - $label: If present, the string to use as the title label.
 *
 * Helper variables:
 * - $job: The fully loaded job object the title belongs to.
 */
?>
<?php if ($title): ?>
  <div class="recruit-job-title">
    <?php if ($label): ?>
      <div class="title-label">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <?php print $title; ?>
  </div>
<?php endif; ?>
