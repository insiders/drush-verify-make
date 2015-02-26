<?php
/**
 * Drush module which verifies the drush makefile with an existing installation path
 * by generating a checksum. It skips the make when the checksums match.
 * 
 * © 2015 Insiders Online
 */


/**
 * Implements hook_make_validate_info()
 */
function verify_make_make_validate_info($info) {
  if (($current_build_path = drush_get_option('verify-make-path', FALSE))) {
    $checksum = _verify_make_checksum(md5(serialize($info)));
    if (file_exists($current_build_path . '/.make_checksum')) {
       $current_checksum = file_get_contents($current_build_path . '/.make_checksum');
       if ($current_checksum === $checksum) {
         drush_log(dt('Build not needed'), 'ok');
         return FALSE;
       }
    }    
  }
  return $info;
}

/**
 * Implements hook_drush_help_alter()
 */
function verify_make_drush_help_alter(&$command) {
  if ($command['command'] == 'make') {
    $command['options']['verify-make-path'] = 'Verify existing installation path checksum';
  }
}

/**
 * Implements drush_MODULE_post_make()
 */
function drush_verify_make_post_make($makefile = NULL, $build_path = NULL) {
  file_put_contents($build_path . '/.make_checksum', _verify_make_checksum());
  drush_log(dt('Make checksum file written.'), 'ok');
}

/**
 * Get or save checksum
 */
function _verify_make_checksum($checksum = '') {
  static $_checksum;
  if ($checksum != '') {
    $_checksum = $checksum;
  }
  return $_checksum;
}

