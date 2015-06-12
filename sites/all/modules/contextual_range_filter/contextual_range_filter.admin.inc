<?php

/**
 * @file
 * contextual_range_filter.admin.inc
 */

/**
 * Menu callback for selecting which filters should become range filters.
 *
 * From a UI perspective it would make sense to simply have a tick-box on the
 * the Views contextual filter configuration panel. The problem is that at that
 * point the argument handler class has already been selected and instantiated.
 * This is why we make the user define the contextual filter first, then have
 * them select on this page which contextual filters need to be converted to
 * range filters.
 */
function contextual_range_filter_admin_config() {

  $range_fields = array(
    'numeric_field_names' => array(), // includes properties like nid
    'string_field_names' => array(),  // includes properties like node:title
    'list_field_names' => array()     // list keys must be integers
  );
  foreach (views_get_all_views() as $view) {
    foreach ($view->display as $display_id => $display) {

      if ($view->set_display($display_id)) {

        $items = $view->get_items('argument', $display_id);

        foreach ($items as $item) {

          $table_data = views_fetch_data($item['table']);
          $field_data = $table_data[$item['field']];

          if (isset($field_data['argument']['handler'])) {

            $handler = $field_data['argument']['handler'];
            $is_numeric_handler = strpos($handler, '_handler_argument_numeric');
            $is_string_handler  = strpos($handler, '_handler_argument_string');
            $is_list_handler    = strpos($handler, '_handler_argument_field_list') || strpos($handler , '_handler_argument_list_range');

            if ($is_numeric_handler || $is_string_handler || $is_list_handler) {

              // We get one field for every $display_id.
              // Should we allow selection per field AND per display ?
              // If not, then we can simplify these nested loops...
              // Currently we find but don't add the "duplicates".
              $title = $field_data['title'];
              $full_name = $item['table'] . ':' . $item['field'];
              $view_name = empty($view->human_name) ? $view->name : $view->human_name;
              if (views_view_is_disabled($view)) {
                $view_name .= ' (' . t('disabled') . ')';
              }
              if ($is_numeric_handler) {
                _contextual_range_filter_add_to_range_fields($range_fields['numeric_field_names'][$full_name], $title, $view_name);
              }
              elseif ($is_string_handler) {
                _contextual_range_filter_add_to_range_fields($range_fields['string_field_names'][$full_name], $title, $view_name);
              }
              elseif ($is_list_handler) {
                _contextual_range_filter_add_to_range_fields($range_fields['list_field_names'][$full_name], $title, $view_name);
              }
            }
          }
        }
      }
    }
  }
  $form['field_names'] = array(
    '#type' => 'fieldset',
    '#title' => t('Select contextual filters to be converted to contextual range filters'),
    '#description' => t('You must first add contextual filters to your views for them to appear on this page.<br/>Once added you use contextual range filters like contextual date filters in that you separate "from" and "to" values by a double hyphen, e.g. http://yoursite.com/yourview/50--149.95 <br/>You may omit the from or to values to create open-ended ranges, e.g. http://yoursite.com/yourview/--149.95 or http://yoursite.com/yourview/50-- <br/>All filter ranges are inclusive of from and to values. Instead of "<strong>--</strong>" you may use a colon "<strong>:</strong>"')
  );
  $types = array(t('numeric'), t('string'), t('list'));
  $type = reset($types);
  foreach ($range_fields as $key => $data) {
    $options = array();
    foreach ($data as $full_field_name => $view_names) {
      $options[$full_field_name] = t('%field in view: @views', array(
        '%field' => reset($view_names), '@views' => implode(', ', array_slice($view_names, 1))));
    }
    $form['field_names']["contextual_range_filter_$key"] = array(
      '#type' => 'checkboxes',
      '#title' => t('Select which of the below contextual <strong>@type</strong> filters should be converted to @type <strong>range</strong> filters:', array('@type' => $type)),
      '#default_value' => variable_get("contextual_range_filter_$key", array()),
      '#options' => $options,
      '#description' => t('')
    );
    $type = next($types);
  }
  return system_settings_form($form);
}

function _contextual_range_filter_add_to_range_fields(&$range_field_view_names, $title, $view_name) {
  if (!isset($range_field_view_names)) {
    $range_field_view_names = array($title);
  }
  if (!in_array($view_name, $range_field_view_names)) {
    $range_field_view_names[] = $view_name;
  }
}