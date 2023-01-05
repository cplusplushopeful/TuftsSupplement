document.addEventListener('DOMContentLoaded', function() {
    let incorrect = document.querySelectorAll('.incorrect');
    let correct = document.querySelector('.correct');
    correct.addEventListener('click', function(){
        correct.style.backgroundColor = 'green';
        document.querySelector('#p').innerHTML = 'Correct';
        for(let i = 0; i < incorrect.length; i++){
            incorrect[i].disabled = true;
        }
    });
    for(let i = 0; i < incorrect.length; i++){
        incorrect[i].addEventListener('click', function() {
            incorrect[i].style.backgroundColor = 'red';
            document.querySelector('#p').innerHTML = 'False';
        });
    }
});


document.addEventListener('DOMContentLoaded', function() {
    let incorrect = document.querySelectorAll('.incorrect2');
    let correct = document.querySelector('.correct2');
    correct.addEventListener('click', function(){
        correct.style.backgroundColor = 'green';
        document.querySelector('#l').innerHTML = 'Correct';
        for(let i = 0; i < incorrect.length; i++){
            incorrect[i].disabled = true;
        }
    });
    for(let i = 0; i < incorrect.length; i++){
        incorrect[i].addEventListener('click', function() {
            incorrect[i].style.backgroundColor = 'red';
            document.querySelector('#l').innerHTML = 'False';
        });
    }
});