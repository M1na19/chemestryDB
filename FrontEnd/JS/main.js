function spawn(atom1){
  var imgholds = document.getElementById('img-spawn');
  imgholds.innerHTML = '<img src="Atomi/' + atom1 + '" alt="Selected Image" style="cursor: pointer;">';
  //var ceva = document.getElementById('notite');
  //ceva.style.display = 'block'; o unealta ce ne poate ajuta mai tarziu
  var ns = document.getElementById('nume-sub');
  ns.style.display = 'block';
}
