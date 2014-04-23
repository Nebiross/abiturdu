<?php

function abitedu_editextinfo_form($form, &$form_state, $node) {
  global $base_url; 

$abitedu = node_load($node->nid);


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
 
	$form['code'] = array(
    '#type' => 'markup',

    '#title' => 'Место рождения',
    '#suffix' =>  "Ваш код - ".$abitedu -> created."<br>"."Состояние вашей анкеты на текущий момент - ".$result."</br><a href='".$base_url."/coderep/".$abitedu->created."'><img src ='http://www.sustec.ru/media/1979'></a></p></p>*&#009;*&#009;*</p>", 
    //'#autocomplete_path' => 'taxonomy/autocomplete/'. $vocabulary->vid,
  );  



  $form['studentnid'] = array(
    '#type' => 'hidden',
    '#default_value' => $node->nid,
  );

  $form['birthday'] = array(
    '#type' => 'date_popup',
    '#title' => 'Дата рождения',
    '#required' => TRUE,
    '#date_format' => 'Y-m-d',
    '#date_year_range' => '-60:-13',
    '#default_value' => date('Y-m-d', $node->birthday ? $node->birthday : strtotime('-16 year')), 
  );

	$form['placebirthday'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => 'Место рождения',
    '#default_value' => $node->placebirthday ? $node->placebirthday : 'г. Челябинск', 
    //'#autocomplete_path' => 'taxonomy/autocomplete/'. $vocabulary->vid,
  );  
  
    $argr = array();
  foreach (taxonomy_get_tree(variable_get('abitedu_grajdan')) as $recgr) {   
    $argr[$recgr -> tid] = $recgr -> name;
  }
  
  $form['grajdan'] = array(
    '#type' => 'select',
      '#required' => TRUE,
    '#title' => 'Гражданство',
    '#options' => $argr,
    '#default_value' => $node->grajdan, 
    '#weight' => 21,
  );
  
$form['sex'] = array(
    '#type' => 'select',
      '#required' => TRUE,
    '#title' => 'Пол',
    '#options' => array(0=>'м', 1=>'ж'),
    '#default_value' => $node->sex, 
    '#weight' => 21,
  );
	
    $ardul = array();
  foreach (taxonomy_get_tree(variable_get('abitedu_dul')) as $recdul) {   
    $ardul[$recdul -> tid] = $recdul -> name;
  }
  
	
	$form['dul'] = array(
    '#type' => 'select',
      '#required' => TRUE,
    '#title' => 'Документ, удостоверяющий личность',
    '#options' => $ardul,
    '#default_value' => $node->dul, 
    '#weight' => 22,
  );
	
	$form['dulserial'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => 'Серия',
    '#default_value' => $node->dulserial, 
    '#weight' => 23,
  ); 
	
	$form['dulnumber'] = array(
    '#type' => 'textfield',
    '#title' => 'Номер',
      '#required' => TRUE,
    '#default_value' => $node->dulnumber, 
    '#weight' => 24,
  ); 
	
	$form['duldate'] = array(
    '#type' => 'date_popup',
    '#title' => 'Дата выдачи',
      '#required' => TRUE,
    '#date_format' => 'Y-m-d',
		'#date_year_range' => '-35:+3',
    '#default_value' => date('Y-m-d', $node->duldate ? $node->duldate : strtotime('-1 year')), 
    '#weight' => 25,
  ); 
	
	$form['dulplace'] = array(
    '#type' => 'textfield',
    '#title' => 'Кем выдан',
      '#required' => TRUE,
    '#default_value' => $node->dulplace, 
    '#weight' => 26,
  ); 
	

	
	$form['telephon'] = array(
    '#type' => 'textfield',
    '#title' => 'Телефон',
    '#default_value' => $node->telephon, 
    '#weight' => 33,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Далее',
    '#weight' => 100,
  );

  return $form;
}




function abitedu_editextinfo_form_validate($form, &$form_state) {

  if (!is_numeric($form_state['values']['dulserial'])) {
    form_set_error('title', 'Серия паспорта  должна быть записано цифрами');
  }
  
  if (!is_numeric($form_state['values']['dulnumber'])) {
    form_set_error('title', 'Номер паспорта  должна быть записано цифрами');
  }
  
if (isset($form_state['values']['dulserial']) and isset($form_state['values']['dulserial'])) {
  
  
     db_update('abitedu')
    ->fields(array(    
      'compl' => '100',
    ))
    ->condition('nid', $form_state['values']['studentnid'])
    ->execute();
  }  

}

function abitedu_editextinfo_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  db_update('abitedu')
    ->fields(array(
      'birthday' => strtotime($values['birthday']),
      'sex' => $values['sex'],
      'placebirthday' => $values['placebirthday'],
      'grajdan' => $values['grajdan'],
      'dul' => $values['dul'],
      'dulserial' => $values['dulserial'],
      'dulnumber' => $values['dulnumber'],
      'duldate' => strtotime($values['duldate']),
      'dulplace' => $values['dulplace'],
     
      'telephon' => $values['telephon'],
    ))
    ->condition('nid', $values['studentnid'])
    ->execute();
 
  $form_state['redirect'] = 'node/' . $values['studentnid'] . '/edu';
}




function abitedu_editeduinfo_form($form, &$form_state, $node) {
   
    global $base_url;

$abitedu = node_load($node->nid);


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
 
	$form['code99'] = array(
    '#type' => 'markup',

    '#title' => 'Место рождения',
    '#suffix' =>  "Ваш код - ".$abitedu -> created."<br>"."Состояние вашей анкеты на текущий момент - ".$result."</br><a href='".$base_url."/coderep/".$abitedu->created."'>Распечатать бумажку</a></p></p>*&#009;*&#009;*</p>", 
    //'#autocomplete_path' => 'taxonomy/autocomplete/'. $vocabulary->vid,
  );  
  $form['studentnid'] = array(
    '#type' => 'hidden',
    '#default_value' => $node->nid,
  );
  
    $arrecoutype = array();
  foreach (taxonomy_get_tree(variable_get('abitedu_outype')) as $recoutype) {   
    $arrecoutype[$recoutype -> tid] = $recoutype -> name;
  }
  
  
  $form['outype'] = array(
    '#type' => 'select',
    '#title' => 'Тип учебного заведения',
    '#options' => $arrecoutype,
    '#default_value' => $node->outype, 
    '#weight' => 40,
  );

  $yearlist = array();
  $curyear = date('Y');
  for ($i = -40 ; $i < 10 ; $i++) {
    $yearlist[$curyear + $i] = $curyear + $i;
  }   
  $form['ouyear'] = array(
    '#type' => 'select',
    '#title' => 'Год окончания учебного заведения',
    '#options' => $yearlist,
    '#default_value' => $node->ouyear ? $node->ouyear : $curyear, 
    '#weight' => 41,
  );

  $form['ounumber'] = array(
    '#type' => 'textfield',
    '#title' => 'Номер учебного заведения, город',
    '#default_value' => $node->ounumber, 
    '#weight' => 42,
  );

  $tmp = array();
  $tmp[] = '9';
  $tmp[] = '11';
  $form['oubase'] = array(
    '#type' => 'select',
    '#title' => 'База',
    '#options' => $tmp,
    '#default_value' => $node->oubase, 
    '#weight' => 43,
  );

  $form['outypedoc'] = array(
    '#type' => 'select',
    '#title' => 'Тип документа об образовании',
    '#options' => array('Аттестат','Диплом','Академическая справка'),
    '#default_value' => $node->outypedoc, 
    '#weight' => 44,
  );
  
  $form['outypedocserial'] = array(
    '#type' => 'textfield',
    '#title' => 'Серия документа об образовании',
    '#default_value' => $node->outypedocserial, 
    '#weight' => 45,
  );

  $form['outypedocnumber'] = array(
    '#type' => 'textfield',
    '#title' => 'Номер документа об образовании',
    '#default_value' => $node->outypedocnumber, 
    '#weight' => 46,
  );

  $form['ousredball'] = array(
    '#type' => 'textfield',
    '#title' => 'Средний балл',
    '#default_value' => $node->ousredball, 
    '#weight' => 47,
  );

  $form['medal'] = array(
    '#type' => 'select',
    '#title' => 'Медаль',
    '#options' => array('Нет','Да'),
    '#default_value' => $node->medal, 
    '#weight' => 48,
    '#description' => 'Аттестат с отличаем, диплом с отличаем',
  );
  
  $arlang = array();
  foreach (taxonomy_get_tree(variable_get('abitedu_lang')) as $reclang) {   
    $arlang[$reclang -> tid] = $reclang -> name;
  }
  
  $form['lang'] = array(
    '#type' => 'select',
    '#title' => 'Иностранный язык',
    '#options' => $arlang,
    '#default_value' => $node->lang, 
    '#weight' => 49,
  );

  $form['olimp'] = array(
    '#type' => 'select',
    '#title' => 'Участие в олимпиадах',
    '#options' => array('Нет','Да'),
    '#default_value' => $node->olimp, 
    '#weight' => 50,
  );
    
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Далее',
    '#weight' => 100,
  );
  
  return $form;
}  


function abitedu_editeduinfo_form_validate($form, &$form_state) {

  if (!is_numeric($form_state['values']['dulserial'])) {
    form_set_error('title', 'Серия паспорта  должна быть записано цифрами');
  }
  
  if (!is_numeric($form_state['values']['dulnumber'])) {
    form_set_error('title', 'Номер паспорта  должна быть записано цифрами');
  }
  
if (isset($form_state['values']['dulserial']) and isset($form_state['values']['dulserial'])) {
  
  
     db_update('abitedu')
    ->fields(array(    
      'compl' => '100',
    ))
    ->condition('nid', $form_state['values']['studentnid'])
    ->execute();
  }  

}


function abitedu_editeduinfo_form_submit($form, &$form_state) {
  $values = $form_state['values'];
    global $base_url;

$abitedu = node_load($node->nid);


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
 
	$form['code'] = array(
    '#type' => 'markup',

    '#title' => 'Место рождения',
    '#suffix' =>  "Ваш код - ".$abitedu -> created."<br>"."Состояние вашей анкеты на текущий момент - ".$result."</br><a href='".$base_url."/coderep/".$abitedu->created."'>Распечатать бумажку</a></p></p>*&#009;*&#009;*</p>", 
    //'#autocomplete_path' => 'taxonomy/autocomplete/'. $vocabulary->vid,
  );  
  $values['ousredball'] = str_replace(',', '.', $values['ousredball']);
  
  db_update('abitedu')
    ->fields(array(
      'ousredball' => $values['ousredball'],
      'outype' => $values['outype'],
      'ouyear' => $values['ouyear'],
      'ounumber' => $values['ounumber'],
      'oubase' => $values['oubase'],
      'outypedoc' => $values['outypedoc'],
      'outypedocserial' => $values['outypedocserial'],
      'outypedocnumber' => $values['outypedocnumber'],
      'medal' => $values['medal'],
      'lang' => $values['lang'],
      'olimp' => $values['olimp'],
    ))
    ->condition('nid', $values['studentnid'])
    ->execute();

  $form_state['redirect'] = 'node/' . $values['studentnid'] . '/ege';
}


function abitedu_editegeinfo_form($form, &$form_state, $node) {
   global $base_url;

$abitedu = node_load($node->nid);


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
 
	$form['code77'] = array(
    '#type' => 'markup',

    '#title' => 'Место рождения',
    '#suffix' =>  "Ваш код - ".$abitedu -> created."<br>"."Состояние вашей анкеты на текущий момент - ".$result."</br><a href='".$base_url."/coderep/".$abitedu->created."'>Распечатать бумажку</a></p></p>*&#009;*&#009;*</p>", 
    //'#autocomplete_path' => 'taxonomy/autocomplete/'. $vocabulary->vid,
  );  
  $yearlist = array();
  $curyear = date('Y');
  for ($i = -40 ; $i < 10 ; $i++) {
    $yearlist[$curyear + $i] = $curyear + $i;
  }   
  
   
  
  $form['studentnid'] = array(
	  '#type' => 'hidden',
	  '#default_value' => $abitedu->nid,
  );
  
  $listd1 = array();
  foreach (taxonomy_get_tree(variable_get('abitedu_ege')) as $recege) {   
    $listd1[$recege -> tid] = $recege -> name;
  }
  
	
  $form['egeset1'] = array(
    '#type'             => 'fieldset',
    '#title'            => 'Предмет ЕГЭ',
  );
  
	$form['egeset1']['egecode1'] = array(
    '#type' => 'select',
    '#title' => 'Название предмета',
    '#options' => $listd1,
    '#default_value' => $abitedu->egecode1, 
    '#weight' => 51,
  );
		
	$form['egeset1']['egeball1'] = array(
    '#type' => 'textfield',
    '#title' => 'Балл',
    '#default_value' => $abitedu->egeball1, 
    '#weight' => 52,
	);
	
	$form['egeset1']['egenum1'] = array(
    '#type' => 'textfield',
    '#title' => 'Наименование и номер документа',
    '#default_value' => $abitedu->egenum1, 
    '#weight' => 53,
	);
  
  $form['egeset1']['egeyear1'] = array(
    '#type' => 'select',
    '#options' => $yearlist,
    '#default_value' => $abitedu->egeyear1 ? $abitedu->egeyear1 : $curyear,
    '#title' => 'Год выдачи документа',
    '#weight' => 54,
	);
	
  $form['egeset2'] = array(
    '#type'             => 'fieldset',
    '#title'            => 'Предмет ЕГЭ',
  );
  
	$form['egeset2']['egecode2'] = array(
    '#type' => 'select',
    '#title' => 'Название предмета',
    '#options' => $listd1,
    '#default_value' => $abitedu->egecode2, 
    '#weight' => 55,
  );
		
	$form['egeset2']['egeball2'] = array(
    '#type' => 'textfield',
    '#title' => 'Балл',
    '#default_value' => $abitedu->egeball2, 
    '#weight' => 56,
	);
	
	$form['egeset2']['egenum2'] = array(
    '#type' => 'textfield',
    '#title' => 'Наименование и номер документа',
    '#default_value' => $abitedu->egenum2, 
    '#weight' => 57,
	);
  
  $form['egeset2']['egeyear2'] = array(
    '#type' => 'select',
    '#options' => $yearlist,
    '#default_value' => $abitedu->egeyear2 ? $abitedu->egeyear2 : $curyear,
    '#title' => 'Год выдачи документа', 
    '#weight' => 58,
	);
	
  $form['egeset3'] = array(
    '#type'             => 'fieldset',
    '#title'            => 'Предмет ЕГЭ',
  );
  
	$form['egeset3']['egecode3'] = array(
    '#type' => 'select',
    '#title' => 'Название предмета',
    '#options' => $listd1,
    '#default_value' => $abitedu->egecode3, 
    '#weight' => 59,
  );
		
	$form['egeset3']['egeball3'] = array(
    '#type' => 'textfield',
    '#title' => 'Балл',
    '#default_value' => $abitedu->egeball3, 
    '#weight' => 60,
	);
	
	$form['egeset3']['egenum3'] = array(
    '#type' => 'textfield',
    '#title' => 'Наименование и номер документа',
    '#default_value' => $abitedu->egenum3, 
    '#weight' => 61,
	);
  
  $form['egeset3']['egeyear3'] = array(
    '#type' => 'select',
    '#options' => $yearlist,
    '#default_value' => $abitedu->egeyear3 ? $abitedu->egeyear3 : $curyear,
    '#title' => 'Год выдачи документа',
    '#weight' => 62,
	);
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Далее',
    '#weight' => 100,
  );
  
  return $form;
}  

function abitedu_editegeinfo_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  


  $values['egeball1'] = str_replace(',', '.', $values['egeball1']);
  $values['egeball2'] = str_replace(',', '.', $values['egeball2']);
  $values['egeball3'] = str_replace(',', '.', $values['egeball3']);
  
  db_update('abitedu')
    ->fields(array(
      'egecode1' => $values['egecode1'],
      'egeball1' => $values['egeball1'],
      'egenum1' => $values['egenum1'],
      'egeyear1' => $values['egeyear1'],
      'egecode2' => $values['egecode2'],
      'egeball2' => $values['egeball2'],
      'egenum2' => $values['egenum2'],
      'egeyear2' => $values['egeyear2'],
      'egecode3' => $values['egecode3'],
      'egeball3' => $values['egeball3'],
      'egenum3' => $values['egenum3'],
      'egeyear3' => $values['egeyear3'],
    ))
    ->condition('nid', $values['studentnid'])
    ->execute();

  $form_state['redirect'] = 'node/' . $values['studentnid'] . '/colleg';

}

function abitedu_editcolleginfo_form($form, &$form_state, $node) {
  
    global $base_url;

$abitedu = node_load($node->nid);


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
 
	$form['code5'] = array(
    '#type' => 'markup',

    '#title' => 'Место рождения',
    '#suffix' =>  "Ваш код - ".$abitedu -> created."<br>"."Состояние вашей анкеты на текущий момент - ".$result."</br><a href='".$base_url."/coderep/".$abitedu->created."'>Распечатать бумажку</a></p></p>*&#009;*&#009;*</p>", 
    //'#autocomplete_path' => 'taxonomy/autocomplete/'. $vocabulary->vid,
  );  
  
  
  
  $form['studentnid'] = array(
	  '#type' => 'hidden',
	  '#default_value' => $abitedu->nid,
  );


  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => 'E-mail',
    '#required' => TRUE,
    '#default_value' => $abitedu->email, 
    '#weight' => 60,
  );
  

  $form['codespec'] = array(
    '#type' => 'select',
    '#title' => 'Специальность',
    '#options' => array('Строители', 'Информационщики', 'Связисты', 'Бухгалтера'),
    '#default_value' => $abitedu->codespec, 
    '#weight' => 60,
  );
  
  
  
	$form['povishuroven'] = array(
    '#type' => 'select',
    '#title' => 'Уровень образования',
    '#options' => array('Базовый','Повышенный', 'Базовый (экспериментальная основная профессиональная образовательная программа с нормативным сроком освоения 4 года)'),
    '#default_value' => $abitedu->povishuroven, 
    '#weight' => 61,
  );
	
	$form['sredobuch'] = array(
    '#type' => 'select',
    '#title' => 'Средства обучения',
    '#options' => array('С полным возмещением затрат','Бюджетные'),
    '#default_value' => $abitedu->sredobuch, 
    '#weight' => 62,
  );
	

	$form['podgotovcurs'] = array(
    '#type' => 'select',
    '#title' => 'Подготовительные курсы',
    '#options' => array('Нет','Да'),
    '#default_value' => $abitedu->podgotovcurs, 
    '#weight' => 65,
  );
	  $lgotlist = array();
  foreach (taxonomy_get_tree(variable_get('abitedu_ege')) as $reclgot) {   
    $lgotlist[$reclgot -> tid] = $reclgot -> name;
  }
  
  	$form['lgoty'] = array(
    '#type' => 'select',
    '#title' => 'Льготы',
    '#options' => $lgotlist,
    '#default_value' => $abitedu->lgoty, 
    '#weight' => 66,
  );
	
	$form['obshaga'] = array(
    '#type' => 'select',
    '#title' => 'В общежитии нуждаюсь',
    '#options' => array('Нет','Да'),
    '#default_value' => $abitedu->obshaga, 
    '#weight' => 67,
  );
	
	if(!$node->lgoty) $tmpp = true; else $tmpp = $abitedu->sredobrazovvpervie; //если льготы нулевые, значит студента добавляют
	$form['sredobrazovvpervie'] = array(
    '#type' => 'select',
    '#title' => 'Получаю среднее проф. обр. впервые',
    '#options' => array('Нет','Да'),
    '#default_value' => $tmpp, 
    '#weight' => 68,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Сохранить',
    '#weight' => 100,
  );
  
  return $form;
}  

function abitedu_editcolleginfo_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  db_update('abitedu')
    ->fields(array(
      'povishuroven' => $values['povishuroven'],
      'sredobrazovvpervie' => $values['sredobrazovvpervie'],
      'codespec' => $values['codespec'],
      'sredobuch' => $values['sredobuch'],
      'podgotovcurs' => $values['podgotovcurs'],
      'lgoty' => $values['lgoty'],
      'email' =>  $values['email'],
      'obshaga' => $values['obshaga'],
    ))
    ->condition('nid', $values['studentnid'])
    ->execute();


}



function printcode($code) {

elibfan_libinclude('mpdf', 'mpdf.php');
    $mpdf = new mPDF('win-1251', 'A4', 0, '', 9, 15,  16, 16, 9, 9);
    $mpdf->SetDisplayMode('fullpage');
   
$html = 'Ваш код';

$mpdf->WriteHtml($html);
		$mpdf->Output('code_sustec.pdf', 'D');
}
