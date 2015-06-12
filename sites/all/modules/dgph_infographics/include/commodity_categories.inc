<?php
function categories_form($form) {
  $form['#tree'] = TRUE;
  $categories = db_select('pm_categories', 'ff')
	->addTag('translatable')
	->fields('ff')
    ->condition('parent', 0)	
	->orderBy('weight')
	->execute()
	->fetchAllAssoc('cid');	
  if(count($categories) > 0):
	  foreach ($categories as $id => $category) {
		$form['category_items'][$id]['name'] = array('#markup' => drupal_placeholder($category->title));
		$form['category_items'][$id]['weight'] = array(
		  '#type' => 'weight',
		  '#title' => t('Weight'),
		  '#title_display' => 'invisible',
		  '#default_value' => $category->weight,
		);
		$form['category_items'][$id]['id'] = array(
		  '#type' => 'hidden',
		  '#value' => $category->cid,
		);
		$form['category_items'][$id]['parent'] = array(
		  '#type' => 'hidden',
		  '#default_value' => $category->parent,
		); 
		
		//$form['category_items'][$id]['edit'] = array('#type' => 'link', '#title' => t('Edit'), '#href' => 'admin/catalog/categories/'.$category->cid.'/edit');
		//$form['category_items'][$id]['delete'] = array('#type' => 'link', '#title' => t('Delete'), '#href' => 'admin/catalog/categories/'.$category->cid.'/delete');
		
		$subcategories = db_select('pm_categories', 's')
		  ->addTag('translatable')
		  ->fields('s')
		  ->condition('parent', $category->cid)	
		  ->orderBy('weight')
		  ->execute()
		  ->fetchAllAssoc('cid');
		if(count($subcategories) > 0) {
		  foreach ($subcategories as $sid => $subcategory) {
			$form['category_items'][$sid]['name'] = array('#markup' => drupal_placeholder($subcategory->title));  
			$form['category_items'][$sid]['weight'] = array(
			  '#type' => 'weight',
			  '#title' => t('Weight'),
			  '#title_display' => 'invisible',
			  '#default_value' => $subcategory->weight,
			);
			$form['category_items'][$sid]['id'] = array(
			  '#type' => 'hidden',
			  '#value' => $subcategory->cid,
			);
			$form['category_items'][$sid]['parent'] = array(
			  '#type' => 'hidden',
			  '#default_value' => $subcategory->parent,
			);
			
			//$form['category_items'][$sid]['edit'] = array('#type' => 'link', '#title' => t('Edit'), '#href' => 'admin/catalog/categories/'.$subcategory->cid.'/edit');
			//$form['category_items'][$sid]['delete'] = array('#type' => 'link', '#title' => t('Delete'), '#href' => 'admin/catalog/categories/'.$subcategory->cid.'/delete');
		  } 	  
		}  		 		 
	  }   
	  $form['actions'] = array('#type' => 'actions');
	  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save changes'));  
  else:
      $form['description'] = array(
        '#type' => 'markup',
        '#title' => t(''),
		'#markup' => t('No Category found')
      );  
  endif;  
  return $form;;
}

function categories_form_submit($form, &$form_state) {
 foreach ($form_state['values']['category_items'] as $id => $data) {
    if (is_array($data) && isset($data['weight'])) {
      db_update('pm_categories')
        ->fields(array('weight' => $data['weight'], 'parent' => $data['parent']))
        ->condition('cid', $id)
        ->execute();
    }
  }
  drupal_set_message(t('Categories ordering has been saved.'));
}

function theme_categories_form($variables) {
  $form = $variables['form'];
  
  drupal_add_tabledrag('text-format-order', 'match', 'parent', 'text-format-order-parent', 'text-format-order-parent', 'text-format-order-id', TRUE, 1);
  drupal_add_tabledrag('text-format-order', 'order', 'sibling', 'text-format-order-weight');
  
  $rows = array();
  if(isset($form['category_items'])):
	  foreach (element_children($form['category_items']) as $id) {	
		$parent = $form['category_items'][$id]['parent']['#default_value'];
		
		$form['category_items'][$id]['parent']['#attributes']['class'] = 'text-format-order-parent';
		$form['category_items'][$id]['id']['#attributes']['class'] = 'text-format-order-id';  
		$form['category_items'][$id]['weight']['#attributes']['class'] = array('text-format-order-weight');	
		$form['category_items'][$id]['parent']['#type'] = 'hidden';		
		
		$indentation = ($parent == 0) ? 0 : 1; 
		
		$row = array();	
		$row[] = theme('indentation', array('size' => $indentation)) . drupal_render($form['category_items'][$id]['name']);
		$row[] = drupal_render($form['category_items'][$id]['weight']) . drupal_render($form['category_items'][$id]['parent']) . drupal_render($form['category_items'][$id]['id']);
		//$row[] = drupal_render($form['category_items'][$id]['edit']);
		//$row[] = drupal_render($form['category_items'][$id]['delete']);
		$row = array_merge(array('data' => $row), $form['category_items'][$id]['#attributes']);
		$row['class'][] = 'draggable';
		$rows[] = $row;	
	  }  
  endif;  
  $header = array(t('Category Name') , t('Weight')/*, array('data' => t('Operations'), 'colspan' => 2)*/);
  
  $output = theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'text-format-order')));
  $output .= drupal_render_children($form);
  return $output;
}