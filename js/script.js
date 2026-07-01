// Bright Future Academy JavaScript

// Mobile Navigation Menu
const menuBtn = document.getElementById("menuBtn");
const navLinks = document.getElementById("navLinks");

if (menuBtn && navLinks) {
  menuBtn.addEventListener("click", function () {
    navLinks.classList.toggle("show");
  });
}

// Admission Form Validation
const admissionForm = document.getElementById("admissionForm");

if (admissionForm) {
  admissionForm.addEventListener("submit", function (event) {
    event.preventDefault();

    const name = document.getElementById("name").value.trim();
    const email = document.getElementById("email").value.trim();
    const phone = document.getElementById("phone").value.trim();

    const formMessage = document.getElementById("formMessage");

    if (name === "" || email === "" || phone === "") {
      formMessage.style.color = "red";
      formMessage.textContent = "Please fill all required fields.";
      return;
    }

    if (!email.includes("@") || !email.includes(".")) {
      formMessage.style.color = "red";
      formMessage.textContent = "Please enter a valid email address.";
      return;
    }

    if (phone.length !== 10 || isNaN(phone)) {
      formMessage.style.color = "red";
      formMessage.textContent =
        "Please enter a valid 10-digit mobile number.";
      return;
    }

    formMessage.style.color = "green";
    formMessage.textContent =
      "Thank you! Your admission enquiry has been submitted successfully.";

    admissionForm.reset();
  });
}

// Contact Form Validation
const contactForm = document.getElementById("contactForm");

if (contactForm) {
  contactForm.addEventListener("submit", function (event) {
    event.preventDefault();

    alert("Thank you for contacting Bright Future Academy. We will get back to you soon.");

    contactForm.reset();
  });
}

// Course Filter Function
function filterCourses(category) {
  const items = document.querySelectorAll(".course-item");

  items.forEach(function (item) {
    if (category === "all" || item.classList.contains(category)) {
      item.style.display = "block";
    } else {
      item.style.display = "none";
    }
  });
}

// Program Information Message
function showProgramInfo() {
  const message = document.getElementById("programMessage");

  if (message) {
    message.textContent =
      "Explore our programs to build skills and prepare for your career.";
  }
}