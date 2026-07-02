// Mobile Navigation Menu
const menuBtn = document.getElementById("menuBtn");
const navLinks = document.getElementById("navLinks");

if (menuBtn && navLinks) {
    menuBtn.addEventListener("click", function () {
        navLinks.classList.toggle("show");
    });
}

// Contact Form Validation
const contactForm = document.getElementById("contactForm");

if (contactForm) {
    contactForm.addEventListener("submit", function (event) {
        event.preventDefault();

        const name = document.getElementById("name").value.trim();
        const email = document.getElementById("email").value.trim();
        const subject = document.getElementById("subject").value.trim();
        const message = document.getElementById("message").value.trim();

        if (name === "" || email === "" || subject === "" || message === "") {
            alert("Please fill in all fields.");
            return;
        }

        alert("Thank you for contacting Bright Future Academy!");
        contactForm.reset();
    });
}

// Admission Form Validation
const admissionForm = document.getElementById("admissionForm");

if (admissionForm) {
    admissionForm.addEventListener("submit", function (event) {
        event.preventDefault();

        const studentName = document.getElementById("studentName").value.trim();
        const studentEmail = document.getElementById("studentEmail").value.trim();
        const studentPhone = document.getElementById("studentPhone").value.trim();
        const studentCourse = document.getElementById("studentCourse").value.trim();

        if (
            studentName === "" ||
            studentEmail === "" ||
            studentPhone === "" ||
            studentCourse === ""
        ) {
            alert("Please complete all required fields.");
            return;
        }

        alert("Admission application submitted successfully!");
        admissionForm.reset();
    });
}

// Welcome Message
window.addEventListener("load", function () {
    console.log("Welcome to Bright Future Academy");
});
