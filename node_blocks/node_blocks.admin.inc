<?php

function node_blocks_settings() {
  $form = array (
    'blocks' => array('#type' => 'fieldset', '#tree' => TRUE),
    '#prefix' => '<p>' . t('Put -1 in part field to remove a block') . '</p>',
  );

  $system_blocks = _block_rehash();
  $js_blocks = array();
  $blocks_info = array();
  foreach ($system_blocks as $block) {
    $js_blocks[ $block['module'] ][ $block['bid'] ] = check_plain($block['info']);
    $blocks_info[ $block['bid'] ] = check_plain($block['info']);
  }
  
  $blocks = variable_get('node_blocks_default', array());
  $blocks[-1] = -1;
  $blocks_info[-1] = t('Add new block');
  $max_part = count($blocks);
  foreach ($blocks as $part => $bid) {
    if ($part >= $max_part) {
      $max_part = $part + 1;
    }
    $form['blocks'][$part] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
    );

    if (!isset($blocks_info[$bid])) {
      $blocks_info[$bid] = t('Missing block');
    }
    $form['blocks'][$part]['block_form'] = array(
      '#type' => 'markup',
      '#value' => '<div class = "block-form-handle"> ' . $blocks_info[$bid] . '</div>',
    );

    $form['blocks'][$part]['block'] = array(
      '#type' => 'hidden',
      '#default_value' => $bid,
    );

    $form['blocks'][$part]['part'] = array(
      '#type' => 'textfield',
      '#title' => t('Part'),
      '#default_value' => $part,
      '#size' => 2,
    );
  }
  $form['blocks'][-1]['part']['#default_value'] = $max_part;
  unset($form['blocks'][-1]['block']['#default_value']);

  drupal_add_js(array('node_blocks' => $js_blocks), 'setting');
  $path = drupal_get_path('module', 'node_blocks');
  drupal_add_js($path . '/node_blocks.js');
  drupal_add_css($path . '/node_blocks.css');

  $form['block_form'] = array(
    '#title' => t('Block selection'),
    '#attributes' => array('style' => 'display:none', 'class' => 'block-form'),
    '#type' => 'fieldset',

    'block_modules' => array(
      '#type' => 'select',
      '#title' => t('By module'),
      '#options' => array_keys($js_blocks),
    ),

    'block_deltas' => array(
      '#type' => 'select',
      '#title' => t('Block title'),
      '#options' => array(),
    ),
    
    'block_operations' => array(
      '#type' => 'markup',
      '#value' => 
        '<div class="block-operations">' .
          '<span class="block-save">' . t('Save') . '</span>' .
          '<span class="block-cancel">' . t('Cancel') . '</span>' .
        '</div>'
        ,
    ),
  );

  array_unshift($form['block_form']['block_modules']['#options'], 'None');

  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

function node_blocks_settings_submit($form, &$form_state) {
  $blocks = array();
  foreach ($form_state['values']['blocks'] as $part => $block) {
    if ($block['part'] != -1 and $block['block']) {
      $blocks[$block['part']] = $block['block'];
    }
  }
  variable_set('node_blocks_default', $blocks);
  cache_clear_all('node-blocks-default', 'cache');
}
