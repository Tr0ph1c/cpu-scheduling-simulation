<?php
$inputs_file = fopen("inputs", "w") or die("cant open inputs");

// SET VARIABLES
$NOP = 1;
$QT = 10;

if (isset($_REQUEST["NOP"]) && isset($_REQUEST["QT"])) 
{
    $QT = $_GET["QT"];
    $NOP = $_GET["NOP"];
    
    fwrite($inputs_file, $_GET["QT"]."\n");
    fwrite($inputs_file, $_GET["NOP"]."\n");

    for ($i = 0; $i < intval($NOP); $i++) {
        if (isset($_GET["P${i}BT"])) fwrite($inputs_file, $_GET["P${i}BT"]."\n");
        if (isset($_GET["P${i}AT"])) fwrite($inputs_file, $_GET["P${i}AT"]."\n");
    }
}
// END SET VARIABLES

// IF PRESSED START EXECUTE MAIN.EXE AND GET OUTPUTS
if (isset($_GET['START_SIM']) && $_GET['START_SIM'] == "1") {
    $results = explode("\n", shell_exec("main.exe"));

    $gantt_chart = array_map("intval", explode(",", $results[0]));

    $results = array_map("floatval", $results);

    $avgWT = $results[1];
    $avgTT = $results[2];
    $avgRT = $results[3];
}
// END EXECUTION

fclose($inputs_file);
?>

<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Round Robin Scheduling Algorithm Simulation</title>
        <link rel="stylesheet" href="style.css">
        <link rel="icon" href="./imgs/icon.ico">
    </head>

    <body>
        <div class="container">
            <div class="section" id="table">
                <h1>Round Robin Scheduling Algorithm Simulation</h1>
                <div class="preq">
                    <div class="inp-box">
                        <label for="QT">Quantum time (ms): </label>
                        <input type="number" id="QT" min="1" max="999" step="1" onchange="setQT();" value="<?php echo $QT; ?>">
                    </div>
    
                    <div class="inp-box">
                        <label for="NOP">Number of processes: </label>
                        <input type="number" id="NOP" min="1" max="100" step="1" onchange="changeNOP();" value=<?php echo $NOP ?>>
                    </div>
                </div>

                <table>
                    <tbody>
                        <tr>
                            <th>PID</th>
                            <th>BT</th>
                            <th>AT</th>
                            <th>WT</th>
                            <th>TT</th>
                            <th>RT</th>
                        </tr>
                    </tbody>
                </table>
                <form action="index.php" method="get" id="inputs">
                    <?php
                    if($_SERVER['REQUEST_METHOD'] === 'GET') {
                        $num_of_rows = $NOP;
                        echo '<table id="s">';
                        for ($i=0; $i < $num_of_rows; $i++) {

                            echo '<tr>';
                            echo "<td>P{$i}</td>";
                            echo "<td class=edit><input class='input-td' min=1 max=999  type=number name='P${i}BT' value=";
                            if (isset($_GET["P${i}BT"])) echo $_GET["P${i}BT"];
                            echo "></td>";
                            echo "<td class=edit><input class='input-td' min=0 max=999  type=number name='P${i}AT' value=";
                            if (isset($_GET["P${i}AT"])) echo $_GET["P${i}AT"];
                            echo "></td>";
                            // WT
                            $WTi = 4 + $i * 3;
                            echo "<td>";
                            if (isset($results[$WTi])) echo $results[$WTi];
                            echo "</td>";
                            // TT
                            $TTi = 5 + $i * 3;
                            echo "<td>";
                            if (isset($results[$WTi])) echo $results[$TTi];
                            echo "</td>";
                            // RT
                            $RTi = 6 + $i * 3;
                            echo "<td>";
                            if (isset($results[$WTi])) echo $results[$RTi];
                            echo "</td>";
                            echo '</tr>';
                        }
                        echo '</table>';
                    }
                    ?>

                <table class="avg-table">
                    <tbody>
                        <tr>
                            <th>Average Waiting Time</th>
                            <th>Average Turn Around Time</th>
                            <th>Average Response Time</th>
                        </tr>
                        <tr>
                            <td>
                                <?php if(isset($results[0])) echo $results[0] ?>
                            </td>
                            <td>
                                <?php if(isset($results[1])) echo $results[1] ?>
                            </td>
                            <td>
                                <?php if(isset($results[2])) echo $results[2] ?>
                            </td>
                        </tr>
                    </tbody>
                </table>
    
                    <button onclick="startSim();" style="margin-top: 10px;" id="btn">Start Simulation</button>

                    <input type="hidden" name="QT" id="QTvar">
                    <input type="hidden" name="NOP" id="NOPvar">
                    <input type="hidden" name="START_SIM" id="START_SIM" value="0">
                </form>
            </div>

            <div class="section" id="gantt">
                <h1>Gantt Chart</h1>
                <div class="gantt">
                <?php
                if (isset($gantt_chart)) {
                    for ($i = 0; $i < (count($gantt_chart) / 3) - 1; $i++) {
                        $Pi = $i * 3;
                        $Si = 1 + $i * 3;
                        $Ei = 2 + $i * 3;
                        $width = ($gantt_chart[$Ei] - $gantt_chart[$Si]) * 20;
                        echo "<div style='width:${width}px'>";
                        echo "<div class='slot'>";
                        echo "<div class='frame'><h4>$gantt_chart[$Pi]</h4></div>";
                        echo "<p>$gantt_chart[$Si]:$gantt_chart[$Ei]</p>";
                        echo "</div>";
                        echo "</div>";
                    }
                }
                ?>
                </div>
            </div>

            <div class="section" id="description">
                <div class="description">
                    <h1>About</h1>
                    <p>Round Robin is a preemptive scheduling algorithm designed for time-sharing systems...</p>
                    <h2><span class="A">A</span>dvantages:</h2>
                    <ul>
                        <li>Fairness: Ensures that each process gets an equal share of CPU time.</li>
                        <li>Preemptive: Allows multiple processes to execute concurrently.</li>
                        <li>Simple Implementation: Easy to understand and implement.</li>
                    </ul>
                    <h2><span class="D">Dis</span>advantages:</h2>
                    <ul>
                        <li>Overhead: Can lead to high context switch overhead, especially with small time quanta.</li>
                        <li>Poor Performance: May not perform well for long-running processes or when the time quantum is too short.</li>
                    </ul>
                </div>
            </div>
        </div>

        <div class="BG"></div>
    </body>

    <script>
        setNOP();
        setQT();

        function changeNOP() {
            NOPval = parseInt(document.getElementById("NOP").value);
            document.getElementById("NOPvar").value = NOPval;

            const form = document.getElementById("inputs");

            form.submit();
        }

        function setNOP() {
            NOPval = parseInt(document.getElementById("NOP").value);
            document.getElementById("NOPvar").value = NOPval;
        }

        function setQT() {
            QTval = parseInt(document.getElementById("QT").value);
            document.getElementById("QTvar").value = QTval;
        }

        function startSim() {
            document.getElementById("START_SIM").value = "1";

            const form = document.getElementById("inputs");

            form.submit();
        }
    </script>
</html>


