<?php




function webform_access_history_options() {

    $form = array();

    $form['wah_selected_style'] = array(
        '#type'=>'textarea',
        '#value'=>variable_get('wah_selected_style', WAH_DEFAULT_HIGHLIGHT_CSS),
        '#title'=>t('CSS style for "New" submissions '),
        '#description'=>t('Please use valid CSS syntax.'),
    );

    $form['wah_allowed_paths'] = array(
        '#type'=>'textarea',
        '#value'=>variable_get('wah_allowed_paths', WAH_DEFAULT_ALLOWED_PATHS),
        '#title'=>t('Allowed execution paths'),
        '#description'=>t('This keeps the action only on certain paths.')
    );


    return system_settings_form($form);



}