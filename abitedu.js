function updateAllFIO() {
	
	document.getElementById("edit-lname").value = UperFirstLetter(document.getElementById("edit-lname").value);
	
	document.getElementById("edit-fname").value = UperFirstLetter(document.getElementById("edit-fname").value);
	
	document.getElementById("edit-sname").value = UperFirstLetter(document.getElementById("edit-sname").value);
	
	document.getElementById("edit-title").value =       document.getElementById("edit-lname").value + " " + document.getElementById("edit-fname").value + " " + document.getElementById("edit-sname").value;
    var rn = new RussianName(document.getElementById("edit-title").value);
    document.getElementById("edit-fiodat").value = rn.fullName(rn.gcaseDat);
    document.getElementById("edit-fiovin").value = rn.fullName(rn.gcaseVin);
    document.getElementById("edit-fiorod").value = rn.fullName(rn.gcaseRod);
};

function UperFirstLetter(originalString) {
    var temp = originalString.charAt(0).toUpperCase();
    temp += originalString.substring(1, originalString.length);
    originalString = temp;
    return originalString;
}

  
  
   jQuery(document).ready(function($) {
      
       $('div.studphoto').append($('div.field-name-field-studphoto'));
   
      
      return false;
    });

