<?php
    $nid = $node->nid;
    $comments = $content['comments'];
    $comment_count = $node->comment_count; 
    if(empty($comment_count)) { $comment_count = "0"; }
    
    $items = $comments['comments'];
    if($comment_count > 0) {
        // Find out how many pictures there are
        $photo_count = 0; 
        foreach($items as $item) { 
            if (!empty($item['comment_body']["#object"]->field_add_a_photo)) {
                $photo_count++;
            }
        }
        // Find out how many video embeds there are 
        $video_count = 0; 
        foreach($items as $item) { 
            if (!empty($item['comment_body']["#object"]->field_embed_video)) {
                $video_count++;
            }
        }
    }
    if (empty($photo_count)) {
        $photo_count = "0"; 
    }
    if (empty($video_count)) {
        $video_count = "0";
    }
    if($comment_count == 1) {
        $comment_tab_text = "1 Comment";
    }
    else {
        $comment_tab_text = $comment_count . " Comments";
    }
    if($photo_count == 1) {
        $photo_tab_text = "1 Photo";
    }
    else {
        $photo_tab_text = $photo_count . " Photos";
    }
    if($video_count == 1) {
        $video_tab_text = "1 Video";
    }
    else {
        $video_tab_text = $video_count . " Videos";
    }
?>

<div id="maindiv" class="node2">
    <div class="row">
        <div id="main" class="large-12 columns">
            <div class="page-title-container">
                <h1 id="page-title" class="title"><?php print $title; ?></h1>
            </div>
            <?php print render($content['field_award_notice_abstract']) ?>
            <div class="philgeps-comments">
                <h4>Comments</h4>
                <ul class="comment-tabs">
                        <li id="tab-comments"><?php echo $comment_tab_text; ?></li>
                        <li id="tab-photos"><?php echo $photo_tab_text; ?></li>
                        <li id="tab-video"><?php echo $video_tab_text; ?></li>
                </ul>
                <div id="philgeps-comments" class="commentsection">
                <?php 
                    if($comment_count > 0) {
                        foreach($items as $cid => $item) {
                            if (is_numeric($cid)) {
                                $author = $item['#comment']->name;
                                $dtCreated = format_interval(time()-$item['#comment']->created);
                ?>
                <div class="clearfix comment">
                    <div class="avatar span1"><img src="http://placehold.it/60x60"></div>
                        <div class="comment-content span11">
                            <?php
                                //unset($item['links']);
                                print "<p class='comment-meta'>$author<span class='comment-date'>about $dtCreated ago</span></p>";
                                print render($item);
                            ?>
                        </div>
                    </div>
                <?php
                            }
                        }
                    }
                    else {
                        print "<div class='comment'><p>No comments have been posted yet.</p></div>";
                    }
                    global $user;
                    $roles = $user->roles;
                    if (in_array('administrator', $roles) || in_array('agency', $roles)) {
                        // renders the add comment form
                        $commentForm = drupal_get_form("comment_node_philgeps_procurement_item_form", (object)array('nid' => $nid));
                        $commentForm['comment_body']['und'][0]['value']['#title'] = '';
                        $commentForm['comment_body']['und'][0]['value']['#attributes']['placeholder'] = t('Your Feedback or Comment');
                        $commentForm['actions']['submit']['#value'] = "Submit Feedback";
                        hide($commentForm['author']);  
                        hide($commentForm['field_add_a_photo']);  
                        hide($commentForm['field_embed_video']);  
                        hide($commentForm['field_add_a_kml_file']);
                        print drupal_render($commentForm);
                    }
                ?>
                </div>
            </div>	
            <?php
                $backUri = "/infographics/philgeps";
                if (array_key_exists('a', $_GET)) {
                    $backUri .= "/".$_GET['a'];
                    if (array_key_exists('y', $_GET)) {
                        $backUri .= "/".$_GET['y'];
                    }
                }
            ?>
            <div class='clear'></div>
            <ul class="back-to-philgeps">
                <li><a href="<?php echo $backUri ?>">&lt;&lt;&nbsp;back to philgeps</a></li>
            </ul>
        </div>
    </div>
</div>