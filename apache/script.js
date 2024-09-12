document.addEventListener('DOMContentLoaded', () => {
    const form = document.getElementById('data-form');
    const dataContainer = document.getElementById('data-container');

    form.addEventListener('submit', async (e) => {
        e.preventDefault();

        const temperature = document.getElementById('temperature').value;
        const humidity = document.getElementById('humidity').value;

        try {
            await fetch('server.php', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded'
                },
                body: `temperature=${encodeURIComponent(temperature)}&humidity=${encodeURIComponent(humidity)}`
            });

            // Update the displayed data
            loadData();
        } catch (error) {
            console.error('Error:', error);
        }
    });

    // Function to load data
    async function loadData() {
        try {
            const response = await fetch('data_log.txt');
            const text = await response.text();
            const lines = text.split('\n').filter(line => line.trim() !== '');

            // Sort lines by timestamp
            lines.sort((a, b) => {
                const timeA = new Date(a.split(' - ')[0]);
                const timeB = new Date(b.split(' - ')[0]);
                return timeB - timeA;
            });

            dataContainer.innerHTML = lines.map(line => `<p>${line}</p>`).join('');
        } catch (error) {
            console.error('Error:', error);
        }
    }

    // Initial load
    loadData();

    // Refresh data every 10 seconds
    setInterval(loadData, 10000);
});
