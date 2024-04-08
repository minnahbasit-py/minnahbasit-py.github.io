

function connectAction(button) {
    var connectTag = button.querySelector('p');
    if (connectTag.textContent === 'Connect') {
        connectTag.textContent = 'Connected';
        connectTag.style.backgroundColor = "#DFFDE0";
    } else {
        button.style.backgroundColor = ''; // Revert to original background color
        connectTag.textContent = 'Connect';
        connectTag.style.backgroundColor = "#FFFFFF"; 
    }
}
