
const wrongmessage = `<p id="incorrect">Incorrect!</p>`;
const correctmessage = `<p id="correct">Correct!</p>`;


function change(button) {
  if (button.className == "wrong") {
    button.style.backgroundColor = "red";
    addmessage(wrongmessage);
  }
  else {
    button.style.backgroundColor = "green";
    addmessage(correctmessage);
  }
  disablebuttons();
}

function addmessage(message) {
  let question1 = document.getElementById("part1");
  question1.insertAdjacentHTML("afterend", message);
}

function disablebuttons() {
  let buttons = document.querySelectorAll(".wrong, .right");
  for (let i = 0; i < buttons.length; i++) {
    buttons[i].disabled = true;
  }
}

function disable(button) {
  button.disabled = true;
}

function checkanswer() {
  let answer = document.getElementById("answer").value;
  let input = document.querySelector("input");
  let question2 = document.getElementById("part2");
  if (answer.toLowerCase() == "no") {
    input.style.backgroundColor = "green";
    question2.insertAdjacentHTML("afterend", `<p>Correct!</p>`);
  }
  else {
    input.style.backgroundColor = "red";
    question2.insertAdjacentHTML("afterend", `<p>Incorrect!</p>`);
  }
  input.style.color = "white";
}
