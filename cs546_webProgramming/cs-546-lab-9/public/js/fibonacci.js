let results = document.getElementById("results");
let indexNum = document.getElementById("indexNum");
let myForm = document.getElementById('myForm');

if (myForm) {
    myForm.addEventListener('submit', (event) => {
        if (indexNum.value === '') {
            alert("Error: must supply a number!");
            return;
        } 
        event.preventDefault();
        let num = parseInt(indexNum.value);
        let front = 1;
        let back = 0;
        let temp = 0;
        if (num < 1) {
            front = 0;
        } else if (num === 1) {
            front = 1;
        } else {
            for(let i = 2; i <= num; i++) {
                temp = back;
                back = front;
                front = front + temp;
            }
        }

        let isPrime = true;
        for(var i = 2; i < front; i++) {
            if(front % i === 0) isPrime = false;
        }
        if (front <= 1) isPrime = false;

        let newLi = document.createElement('li');
        newLi.innerHTML = `The Fibonacci of ${num} is ${front}.`;
        if (isPrime) {
            newLi.classList.add("is-prime");
        } else {
            newLi.classList.add("not-prime");
        }
        results.appendChild(newLi);
    });
}
