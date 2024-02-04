let box1 = document.getElementById('atom-add1');
//let box2 = document.getElementById('img-holder2');



function spawn(atom1){
  var imgholds = document.getElementById('img-spawn');
  imgholds.innerHTML = '<img src="Atomi/' + atom1 + '" alt="Selected Image" style="cursor: pointer;">';
  atom2 = atom1;
}

function killOrTransFirstImage() {
  var img1 = document.getElementById('atom-holder1');
  var img2 = document.getElementById('atom-holder2');
  if(img2.innerHTML!=''){
    img1.innerHTML = img2.innerHTML;
    img2.innerHTML= '';
  } else{
    img1.innerHTML = '';
  }
}

function killSecondImage() {
  var img2 = document.getElementById('atom-holder2');
  img2.innerHTML='';
}