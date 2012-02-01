<?php

/**
 * @file
 * Default theme implementation to present the SKU on a job page.
 *
 * Available variables:
 * - $sku: The SKU to render.
 * - $label: If present, the string to use as the SKU label.
 *
 * Helper variables:
 * - $job: The fully loaded job object the job reference represents.
 */
?>
<?php if ($job_ref): ?>
  <div class="recruit-job-job-ref">
    <?php if ($label): ?>
      <div class="job-ref-label">
        <?php print $label; ?>
      </div>
    <?php endif; ?>
    <?php print $job_ref; ?>
  </div>
<?php endif; ?>
