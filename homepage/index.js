document.addEventListener("DOMContentLoaded", function() {
    const title = document.getElementById("title");
    const texts = document.querySelectorAll(".categories-text")
    const observer = new IntersectionObserver((entries)=>{
      entries.forEach((entry) => {
          entry.target.classList.toggle("loaded", entry.isIntersecting);
          console.log("function done");
        });
      });
    observer.observe(title);
    texts.forEach( text => {
      observer.observe(text);
    })
  });
