<?php
/**
 * @file
 * Theme implementation to display information about the post/profile author.
 *
 * See author-pane.tpl.php in Author Pane module for a full list of variables.
 */
?>

<?php
  // This bit of debugging info will show the full path to and name of this
  // template file to make it easier to figure out which template is
  // controlling which author pane.
  if (!empty($show_template_location)) {
    print __FILE__;
  }
?>

<div class="author-pane">
 <div class="author-pane-inner">
    <?php /* General section */ ?>
    <div class="author-pane-section author-pane-general">
      <?php /* Account name */ ?>
      <div class="author-pane-line author-name">
        <?php print $account_name; ?>
      </div>

      <?php /* User picture / avatar (has div in variable) */ ?>
      <?php if (!empty($picture)): ?>
        <?php print $picture; ?>
      <?php endif; ?>

      <?php /* Last active */ ?>
      <?php if (!empty($last_active)): ?>
        <div class="author-pane-line">
           <span class="author-pane-label"><?php print t('Last seen'); ?>:</span> <?php print t('!time ago', array('!time' => $last_active)); ?>
        </div>
      <?php endif; ?>

      <?php /* Joined */ ?>
      <?php if (!empty($joined)): ?>
        <div class="author-pane-line author-joined">
          <span class="author-pane-label"><?php print t('Joined'); ?>:</span> <?php print $joined; ?>
        </div>
      <?php endif; ?>

      <?php /* Posts */ ?>
      <?php if (isset($user_stats_posts)): ?>
        <div class="author-pane-line author-posts">
          <span class="author-pane-label"><?php print t('Posts'); ?>:</span> <?php print $user_stats_posts; ?>
        </div>
      <?php endif; ?>

    </div>

  </div>
</div>
