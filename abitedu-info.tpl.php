 
 <?php 
    global $base_url;

$abitedu = node_load($nid);


	$result = db_select('abitedu', 'a')
			->fields('a', 
				array('status'))
      ->condition('nid', $abitedu -> nid, '=')
			->execute()
			->FetchField();	
   
  $result2 = db_select('abitedu', 'a')
			->fields('a', 
				array('code'))

			->execute()
			->FetchField();	

echo "Ваш код - ".$abitedu -> created."<br>";
echo "Состояние вашей анкеты на текущий момент - ".$result;

print "</br><a href='".$base_url."/coderep/".$abitedu->created."'>Распечатать бумажку</a></br>";

    print '[<a  href="/node/'.($nid) .'">'.($abitedu->syslogin) .'</a>] ['.l('Группа','node/'.$abitedu->parentnid) .']';
    
    print '<div class="abitedu_actionbar">';
    print module_invoke('elibfan_buttons', 'getbuttons', 'abitedu', $nid, 'imgbar');
echo "инфо файл";
  ?>
  
  </div>
