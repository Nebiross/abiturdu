<div class="studenteduinfo">

 
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

    echo "Литинфо";
   # print '<div class="clearfix"><div class="studentedu-fio"><a href="/node/'.($nid) .'">'.($studentedu->fio).'</a> [<a  href="/node/'.($nid) .'">'.($studentedu->syslogin) .'</a>] ['.l('Группа ' . node_load($studentedu->parentnid)->title,'node/'.$studentedu->parentnid) .']';
  #  print '</div><div class="studentedu_actionbar">';
    
   # print module_invoke('libedu', 'getbuttons', 'studentedu', $nid, 'imgbar');
  ?>
  
  </div>
  </div>
 
</div>
