<?php

/**
 * @file
 * Default theme implementation to present the title on a application page.
 *
 * Available variables:
 * - $name: The name to render.
 * - $label: If present, the string to use as the name label.
 *
 * Helper variables:
 * - $application: The fully loaded application object the name belongs to.
 */
?>
<?php if ($name): ?>
  <div class="recruit-application-name">
    <?php if ($label): ?>
      <div class="name-label">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <?php print $name; ?>
  </div>
<?php endif; ?>
