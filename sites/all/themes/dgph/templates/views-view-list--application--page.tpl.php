<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php print $wrapper_prefix; ?>
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <div class="row">
  <div class="large-12 columns">
    <?php foreach ($rows as $id => $row): ?>
      <div class="<?php print $classes_array[$id]; ?>"><?php print $row; ?></div>
    <?php endforeach; ?>
  </div>
</div>