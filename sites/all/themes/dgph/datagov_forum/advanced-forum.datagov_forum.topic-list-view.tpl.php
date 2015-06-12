<?php
/**
 * @file views-view-table.tpl.php
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $class: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * @ingroup views_templates
 */
 $col_width = array();

switch(sizeof($header)){
	case '4':
		 $col_width['title'] = 'large-6';
		 //$col_width['comment_count'] = 'large-2';
		 $col_width['totalcount'] = 'large-2';
		 //$col_width['last_updated'] = 'large-2';
		 $col_width['name'] = 'large-4';
		break;
	case '5':
		 $col_width['title'] = 'large-6';
		 $col_width['comment_count'] = 'large-2';
		 $col_width['totalcount'] = 'large-2';
		 $col_width['last_updated'] = 'large-2';
		 //$col_width['name'] = 'large-2';
		break;
	case '6':
		 $col_width['title'] = 'large-4';
		 $col_width['comment_count'] = 'large-2';
		 $col_width['totalcount'] = 'large-2';
		 $col_width['last_updated'] = 'large-2';
		 $col_width['name'] = 'large-2';
		break;
	default:
		 $col_width['title'] = 'large-6';
		 $col_width['comment_count'] = 'large-2';
		 $col_width['totalcount'] = 'large-2';
		 $col_width['last_updated'] = 'large-2';
		 //$col_width['name'] = 'large-2';
		break;
}
?>
 <div id="forum-topic-list">
  <?php if (!empty($title)) : ?>
    <caption><?php print $title; ?></caption>
  <?php endif; ?>

  <div class="forum-table forum-table-topics <?php print $classes; ?>"><!-- table -->
    <div class="forum-topics-headers"><!-- table header  -->
      <div class="row"><!-- table row (tr)  -->
        <?php foreach ($header as $field => $label): ?>
		<?php if($field!='topic_icon'): ?>
          <div class="<?php print $col_width[$field]; ?> columns views-field views-field-<?php print $fields[$field]; ?>"><!-- th  -->
            <?php print $label; ?>
          </div><!-- th close  -->
        <?php endif; endforeach; ?>
      </div><!-- table row close (tr)  -->
    </div><!-- table header close  -->
    <div><!-- tbody  -->
      <?php foreach ($rows as $count => $row): ?>

        <div class="row <?php print implode(' ', $row_classes[$count]); ?>"><!-- tr  -->
          <?php if (empty($shadow[$count])): ?>
            <?php foreach ($row as $field => $content): ?>
              <?php /* To add popup from teaser in the title of the td, add: title="<?php print $teasers[$count] ?>"*/ ?>

			  <?php if($field!='topic_icon'): ?>
              <div class="<?php print $col_width[$field]; ?> columns views-field views-field-<?php print $fields[$field]; ?>">
               <?php /* Extra label for stickies. */ ?>
               <?php if ($field == 'title' && !empty($sticky[$count])): ?>
                 <span class="sticky-label"><?php print t('Sticky:'); ?></span>
               <?php endif; ?>

               <?php if ($field == 'title'): ?>
			     <?php print $row['topic_icon']; ?>
                 <?php print $row['title']; ?>
			   <?php else: ?>
				  <?php print $content; ?>
               <?php endif; ?>   
			   
              </div>
			  <?php endif; ?>

            <?php endforeach; ?>
          <?php else: ?>
            <?php /* For shadow posts, we print only the icon and themed notice. */ ?>
			<?php if($field!='topic_icon'): ?>
            <div class="<?php print $col_width[$field]; ?> columns views-field views-field-<?php print $fields['topic_icon']; ?>">
              <?php print $row['topic_icon']; ?>
            </div>
			<?php endif; ?>
            <div class="<?php print $col_width[$field]; ?> columns views-field views-field-<?php print $fields['title']; ?>" colspan="<?php print count($header)-1; ?>">
               <?php print $shadow[$count]; ?>
            </div>
          <?php endif; ?>
        </div><!-- tr close -->
      <?php endforeach; ?>
    </div><!-- tbody close -->
  </div><!-- table close -->
</div>