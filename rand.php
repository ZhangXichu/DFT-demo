<?php header('Content-type: plain/text'); ?>
<?php 
for ($i=0;$i<512*512;$i++) {
echo rand(0,255)."\n";
}

?>

