<?php
/**
 * @author Bruno Massa http://drupal.org/user/67164
 * @author TJ (based on his Chart module)
 * @file
 * Use Charts for Drupal administration
 */

/**
 * Implementation of hook_menu().
 */
function charts_system_menu() {
  $items['admin/reports/charts'] = array(
    'access arguments'  => array('access site reports'),
    'file'              => 'charts_system.inc',
    'page callback'     => '_charts_system_charts',
    'page arguments'    => array('nodes'),
    'title'             => 'Charts'
  );
  $items['admin/reports/charts/nodes'] = array(
    'access arguments'  => array('access site reports'),
    'file'              => 'charts_system.inc',
    'page callback'     => '_charts_system_charts',
    'page arguments'    => array('nodes'),
    'title'             => 'Nodes',
    'type'              => MENU_DEFAULT_LOCAL_TASK
  );
  $items['admin/reports/charts/users'] = array(
    'access arguments'  => array('access site reports'),
    'file'              => 'charts_system.inc',
    'page callback'     => '_charts_system_charts',
    'page arguments'    => array('users'),
    'title'             => 'Users',
    'type'              => MENU_LOCAL_TASK
  );
  $items['admin/reports/charts/watchdog'] = array(
    'access arguments'  => array('access site reports'),
    'file'              => 'charts_system.inc',
    'page callback'     => '_charts_system_charts',
    'page arguments'    => array('watchdog'),
    'title'             => 'Watchdog',
    'type'              => MENU_LOCAL_TASK
  );

  return $items;
}
