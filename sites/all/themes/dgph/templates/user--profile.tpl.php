<?php    // load account information    module_load_include('inc', 'user', 'user.pages');    global $user;    $account = user_load($user->uid);    $form = drupal_get_form('user_profile_form', $account);    // load recently viewed datasets    $viewed = dgph_ckan_get_viewed_datasets();    // load favorite datasets    $favs = dgph_ckan_get_favorite_datasets();    // load forums    $terms = advanced_forum_forum_load(0);    $forums = array();    foreach($terms->forums as $item) {        if (1==$item->depth) {            $forums[$item->tid] = $item;        }    }    krsort($forums, SORT_NUMERIC);    // load comments    $comments = comment_get_recent();?><?php    $errMsg = isset($_SESSION['dgph_last_error']) ? $_SESSION['dgph_last_error'] : null;    if (!empty($errMsg)) {?>    <div class="messages error">        <h2 class="element-invisible">Error message</h2>        <ul>            <li>                <em class="placeholder">Error</em>                : <?php print $errMsg ?>            </li>        </ul>    </div><?php        unset($_SESSION['dgph_last_error']);    }?><div class="row news-con">    <div class="large-12 columns subpage-title">        <h1>My Account</h1>    </div></div><div class="row news-con">    <div class="large-3 columns datarequest">        <div class="picturup">            <form class='custom' accept-charset="UTF-8" method="post" action="/user/update-picture" enctype="multipart/form-data">            <input type="hidden" name="form_id" value="<?php print render($form['#form_id']); ?>" />            <input type="hidden" name="form_build_id" value="<?php print render($form['#build_id']); ?>" />            <input type="hidden" name="form_token" value="<?php print render($form['form_token']['#default_value']); ?>" />            <?php print render($form['picture']) ?>            </form>        </div>        <div id="accordion" class='sidebar-accordion'>            <h3>Basic Information</h3>            <div>                <p style="display:block;">                <div class="basicInformation">                    <form class='custom' accept-charset="UTF-8" method="post" action="/user/update-basic">                        <input type="hidden" name="form_id" value="<?php print render($form['#form_id']); ?>" />                        <input type="hidden" name="form_build_id" value="<?php print render($form['#build_id']); ?>" />                        <input type="hidden" name="form_token" value="<?php print render($form['form_token']['#default_value']); ?>" />                        <?php print render($form['field_first_name']) ?>                        <?php print render($form['field_last_name']) ?>                        <?php print render($form['account']['mail']) ?>                        <input name="Update" type="submit" value="Update" class="updatesubmit">                    </form>                </div>                </p>            </div>            <h3>Change password</h3>            <div>                <div class="basicInformation">                    <form class='custom' accept-charset="UTF-8" method="post" action="/user/update-password">                    <label>Old Password</label>                     <input type="password" name="old_password" class="form-text">                    <label>New Password</label>                     <input type="password" name="new_password" class="form-text">                    <label>New Password Confirm</label>                     <input type="password" name="new_password_confirm" class="form-text">                    <input name="Update" type="submit" value="Update" class="updatesubmit">                    </form>                </div>            </div>        </div>    </div>    <div class="large-9 columns myaccount">        <?php            $favsCount = count($favs);        ?>        <div id="accordion2">            <h3>                <div class="favoritetab">                    <div class="favoritetabtitle">FAVORITE DATASETS<span><?php echo $favsCount ?></span></div>                </div>            </h3>            <div>                <?php                    $idx = 0;                    while (!empty($favs)) {                        $finfo = array_shift($favs);                        $clsId = ($idx%3)+1;                ?>                <div class="col-<?php echo $clsId ?> col">                    <a title="Download" class="downlad" href="/catalogue/dataset/<?php echo $finfo['name'] ?>">View</a>                    <h1><?php echo $finfo['title'] ?></h1>                    <p><?php echo $finfo['notes'] ?></p>                    </div>                <?php                        $idx++;                    }                ?>                <div class="view-line"><a class="view-all" href="/catalogue">VIEW ALL</a></div>            </div>            <h3>             	<div class="favoritetab">                    <div class="favoritetabtitle history">History </div>	                 </div>             </h3>            <div>             <div class="history-col history-col-1">             	<h1>Data View</h1>                <a href="#" class="date">Date</a>                <div class="clear"></div>                <?php                    $idx = 0;                    while (($idx<6) && !empty($viewed)) {                        $vinfo = array_shift($viewed);                        $tm = strtotime($vinfo['tm']);                        $uname = $vinfo['user_name'];                        $cls = (0==$idx%2) ? 'even' : 'odd';                ?>                <div class="<?php echo $cls ?>">                    <!--<h2><a title="Download" class="downlad" href="/catalogue/dataset/<?php echo $vinfo['name'] ?>"><?php echo $vinfo['title'] ?></a></h2>-->                    <p><?php echo $tm.' / '.$uname ?></p>                    </div>                <?php                        $idx++;                    }                ?>                <div class="view">            	<a style="float:left;" href="/catalogue">View All</a>                </div>             </div>             <div class="history-col history-col-2">             	<h1>Comments</h1>                <a href="#" class="date">Date</a>                <div class="clear"></div>                <?php                    $idx = 0;                    while ($idx<6 && !empty($comments)) {                        $cinfo = array_shift($comments);                        $cls = (0==($idx%2)) ? 'even' : 'odd';                        $name = $cinfo->name;                        $tm = $cinfo->created;                        $subj = $cinfo->subject;                ?>                <div class="<?php echo $cls ?>">                    <h2><?php echo date('M j, Y', $tm).' / '.$name ?></h2>                    <p><?php echo $cinfo->subject ?></p>                </div>                <?php                        $idx++;                    }                 ?>                 <div class="clear"></div>                <div class="view">            	<a style="float:left;" href="/news/latest">View All</a>                </div>             </div>             <div class="history-col history-col-3">             	<h1>Forums</h1>                <a href="#" class="date">Date</a>                <div class="clear"></div>                <?php                    $idx = 0;                    while ($idx<6 && !empty($forums)) {                        $finfo = array_shift($forums);                        $cls = (0==($idx%2)) ? 'even' : 'odd';                        $descr = $finfo->description;                        if (strlen($descr)>25) {                            $descr = substr($descr, 0, 25).'...';                        }                ?>                <div class="<?php echo $cls ?>">                    <h2><?php echo $finfo->name ?></h2>                    <p><?php echo  $descr ?></p>                </div>                <?php                        $idx++;                    }                 ?>                <div class="clear"></div>                <div class="view">            	<a style="float:left;" href="/forum/latest">View All</a>                </div>             </div>            </div>       </div>    </div></div>