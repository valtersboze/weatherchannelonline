<?php
/**
 * @file
 * Include file for weatherchannelonline module.
 */

$plugin = array(

  'title' => t('Last logged in'),
  'description' => t('Show last logged in for auth user.'),
  'single' => TRUE,
  'content_types' => array('weatherchannelonline'),
  'render callback' => 'weatherchannelonline_content_type_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'edit form' => 'weatherchannelonline_content_type_edit_form',
  'category' => array(t('Activity'), -9),
  
);

/**
 * Ctools edit form.
 */
function weatherchannelonline_content_type_edit_form($form, &$form_state) 
{

	$conf = $form_state['conf'];
	$form['weatherchannelonline_label'] = array(
		'#type' => 'textfield',
		'#title' => t('Label'),
		'#description' => t('Login text'),
		'#default_value' => !empty($conf['weatherchannelonline_label']) ? $conf['weatherchannelonline_label'] : 'You last logged in at  ',
  );
  
  return $form;
}

function weatherchannelonline_content_type_edit_form_submit($form, &$form_state) 
{
	foreach (array('weatherchannelonline_label') as $key) {
		$form_state['conf'][$key] = $form_state['values'][$key];
	}
}

/**
 * Render callback function.
 */
function weatherchannelonline_content_type_render($subtype, $conf, $args, $context) 
{

	global $user;
	
	$block = new stdClass();
   
   $logintext = ((isset($user->data['customlogintext']) && ($user->data['customlogintext'] != '')) ? $user->data['customlogintext'] : 'You last logged in at ');
	$logindate = ((isset($user->data['lastloggedin']) && ($user->data['lastloggedin'] != '')) ? $user->data['lastloggedin'] : 'Just now');

	$block->content = 'pane content';
	$block->content = array(
	
		'#markup' => t("@text <br>@date", array('@text' => $logintext, '@date' => $logindate)),
  );

  return $block;
}
