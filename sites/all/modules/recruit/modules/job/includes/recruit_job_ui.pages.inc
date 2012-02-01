<?php

/**
 * @file
 * Page callbacks functions for Job UI module.
 */

/**
 * Menu callback for public job display. uri: recruit-job/*
 */
function recruit_job_ui_view_page($job) {
  // Set page title.
  drupal_set_title(check_plain($job->title));
  
  // Return entity view.
  return $job->view();
}

/**
 * Menu callback for administration job display. uri: admin/recruit/jobs/1*
 */
function recruit_job_ui_admin_view_page($job) {
  return $job->view('admin');
}