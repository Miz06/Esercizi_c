//settaggio del countdown
const countdownDuration = 0.1; // Durata in minuti
const countdownDate = new Date().getTime() + countdownDuration * 60 * 1000; //Imposta la scadenza

// Aggiorna il countdown ogni secondo
const countdownInterval = setInterval(function () {
    const now = new Date().getTime();
    const distance = countdownDate - now;

    // Calcola minuti e secondi
    const minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((distance % (1000 * 60)) / 1000);

    // Mostra il risultato nell'elemento countdown
    document.getElementById("countdown").innerHTML = `${minutes}m ${seconds}s`;

    // Se il countdown è finito, disabilita tutto e mostra un messaggio
    if (distance < 0) {
        clearInterval(countdownInterval);
        document.getElementById("countdown").innerHTML = "Countdown terminato!";
        disableAllInputs();
    }
}, 1000);

// Funzione per disabilitare tutti i campi input
function disableAllInputs() {
    // Disabilita tutte le radio buttons
    document.querySelectorAll('input[type="radio"]').forEach(input => input.disabled = true);

    // Disabilita tutte le textarea
    document.querySelectorAll('textarea').forEach(textarea => textarea.disabled = true);

    // Disabilita il pulsante submit
    const submitButton = document.querySelector('.btn-primary');
    if (submitButton) submitButton.disabled = true;
}

function submitAnswers() {
    let answers = ""; // Variabile per raccogliere tutte le risposte

    // Recupera le risposte alle domande a scelta multipla (radio buttons)
    // vengono selezionate solamente le card che non fanno parte del carosello
    const allQuestions = document.querySelectorAll('.card:not(.carousel-caption .card)'); // Esclude le card del carosello
    allQuestions.forEach(question => {
        const questionText = question.querySelector('.card-header').textContent.trim();
        const selectedRadio = question.querySelector('input[type="radio"]:checked');

        if (selectedRadio) {
            answers += `${questionText}: ${selectedRadio.value}\n`;
        } else {
            answers += `${questionText}: Nessuna risposta selezionata\n`;
        }
    });

    // Recupera le risposte alle domande aperte (textarea) solo dal carosello
    const openQuestions = document.querySelectorAll('.carousel-item textarea');
    openQuestions.forEach((textarea, index) => {
        const questionText = `Domanda ${index + 1}`;
        const answer = textarea.value.trim();

        answers += `${questionText}: ${answer || "Nessuna risposta inserita"}\n`;
    });

    // Crea un file di testo con le risposte
    const blob = new Blob([answers], { type: "text/plain" });
    const link = document.createElement('a');
    link.href = URL.createObjectURL(blob);
    link.download = "risposte.txt"; // Nome del file
    link.click(); // Simula il click per scaricare il file
    // Nella pratica serve a far avviare automaticamente il download del file senza 
    // che lo debba fare manualmente l'utente cliccando su un link

    disableAllInputs();
}
