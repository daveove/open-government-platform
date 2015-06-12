<?php if ($page == 0): ?>

<?php 
if(node_access('update',$node)) {
	print '<div class="node-edit">' . l('Edit', 'node/'.$node->nid.'/edit', $options = array('query'=>array('destination'=>$_GET['q']))) . '</div>';
}


?>



<?php else: ?>

<?php

$description = '';
if(sizeof($node->body)){
	$description = $node->body['und'][0]['value'];
}
$developed_by = '';
if(sizeof($node->field_submitter_name)){
	$developed_by = $node->field_submitter_name['und'][0]['value'];
}
$data_set_used = '';
if(sizeof($node->field_uses_dataset)){
	$data_set_used = $node->field_uses_dataset['und'][0]['value'];
}
$submitted_by  = '';
if(sizeof($node->field_submitter_email)){
	$submitted_by = $node->field_submitter_email['und'][0]['value'];
}

$screen_shot = '';
if(sizeof($node->field_screen_shot)){
	$$screen_shot = '<img src="'.file_create_url($node->field_screen_shot['und'][0]['uri']).'" alt="'.$title.'" title="'.$title.'" />';
}

?>

<div class="appsdetail-page">
  <div class="socialbutton"></div>

  <div class="fivestarrating">
	<?php print render($content['field_apps_rating']); ?>	
  </div>

  <?php if ($content['field_category']): ?>
  <div class="row firstrow">
    <div class="large-12 columns">
      <label>Category / </label><?php print render($content['field_category']); ?>
    </div>
  </div>
  <?php endif; ?>

  <div class="row secondrow">
    <div class="large-6 columns">
      <label>Location / </label>
      <span>&nbsp;National</span> </div>
    <div class="large-6 columns">
      <label>Uploaded / </label>
      <span><?php print date('M d, Y', $node->created); ?></span> </div>
  </div>

  <?php if($description): ?>
  <div class="row thirdrow">
    <div class="large-12 columns">
      <div><label>Description / </label></div>
	  <div style="clear:both;"><?php print $description; ?></div>
    </div>
  </div>
  <?php endif; ?>


  <?php if ($developed_by): ?>
  <div class="row fourthrow">
    <div class="large-12 columns">
      <label>Developed By / </label><span><?php print $developed_by; ?></span>
    </div>
  </div>
  <?php endif; ?>

  <?php if ($data_set_used): ?>
  <div class="row fifthrow">
    <div class="large-12 columns">
      <label>Data Set Used / </label><span><?php print $data_set_used; ?></span>
    </div>
  </div>
  <?php endif; ?>

  <?php if ($submitted_by): ?>
  <div class="row sixthrow">
    <div class="large-12 columns">
      <label>Submitted By / </label><span><?php print $submitted_by; ?></span>
    </div>
  </div>
  <?php endif; ?>


  <?php if($description): ?>
  <div class="row thirdrow screen_shot">
    <div class="large-12 columns">
      <div><label>Screenshots of the App / </label></div>
	  <div style="clear:both;"><?php print $$screen_shot; ?></div>
    </div>
  </div>
  <?php endif; ?>




</div>



<?php endif; ?>

