<div class="row">
	<div class="login-con-area">

		<div class="large-5 columns">
			<div class="login-left">
                <h4>Login</h4>
                <label>User Name</label>
                <div class="clear"></div>
                <input id="edit-name" name="name" type="text" class="name">
                <label>Password</label>
                <div class="clear"></div>
                <input id="edit-pass" name="pass" type="password" class="password">
                <label>Remember me</label><input type="checkbox" id="checkbox1" style="display: none;">
                <span id="custom-checkbox1" class="custom checkbox"></span>
                <div class="clear"></div>
                <?php
                    print drupal_render($form['form_id']);
                    print drupal_render($form['form_build_id']);
                ?>
                <input id="edit-submit" name="enter" type="submit" value="enter">
                <div class="clear"></div>
                <p><?php print l('Forgot your password?', 'user/password'); ?>  /  <?php print l('report problems', 'contact-us') ?></p>
            </div>
		</div>

		<div class="large-2 columns">
			<div class="login-mid"><img src="/sites/all/themes/dgph/images/or.png" width="23" height="117"></div>
		</div>

		<div class="large-5 columns">
            <div class="login-right">
				<?php
				  if (variable_get('fboauth_id', '') && !fboauth_fbid_load()) {
					// Set the redirect to the current page (unless we're on the login page).
					$redirect = (arg(0) === 'user' && (arg(1) === 'login' || arg(1) == '')) ? NULL : $_GET['q'];
					print fboauth_action_display('connect', $redirect);
				  }
				?>
                <img class="facebooklogin" src="/sites/all/themes/dgph/images/facebook-login-btn.png" alt="">
                <!--<img class="twitterlogin" src="/sites/all/themes/dgph/images/twitterlogin-btn.png" alt="">-->
            </div>
		</div>

	</div>
</div>
