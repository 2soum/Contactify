// Simuler une notification
function notifier(message) {
    const notifications = document.getElementById("notifications");
    notifications.innerText = message;
    notifications.style.display = "block";
    setTimeout(() => {
        notifications.style.display = "none";
    }, 3000);
}

// Ajout d'un contact (à connecter avec le backend)
document.getElementById("add-contact-form").addEventListener("submit", (e) => {
    e.preventDefault();
    const nom = document.getElementById("nom").value;
    const prenom = document.getElementById("prenom").value;
    const telephone = document.getElementById("telephone").value;
    const email = document.getElementById("email").value;

    // Simuler un ajout
    notifier(`Contact ${nom} ajouté avec succès !`);

    // Réinitialiser le formulaire
    e.target.reset();
});
