function guiGET(dia_chi) {
	var xhr = new XMLHttpRequest();
	xhr.open("GET", dia_chi, true);
	xhr.timeout = 3000;
	xhr.send();
}

function guiPOST(dia_chi, noi_dung) {
	var xhr = new XMLHttpRequest();
	xhr.open("POST", dia_chi);
	xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
	xhr.send(noi_dung);
}

function vao_xe() {
	var xhr = new XMLHttpRequest();
	xhr.open('POST','/handle_control' );
	xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
	xhr.onload = function() {
		document.body.innerHTML = "";
		document.write(xhr.response);
	};
	xhr.send('cua=vao');
}

function ra_khoi_xe() {
	var xhr = new XMLHttpRequest();
	xhr.open('POST','/handle_control' );
	xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
	xhr.onload = function() {
		document.body.innerHTML = "";
		document.write(xhr.response);
	};
	xhr.send('cua=ra');
	window.onbeforeunload = function(){
		return ;
	};
	window.onunload = function() {
		return;
	};
	connection.close();
}



