<?php 
    // connect to db
    $connect = mysqli_connect("127.0.0.1", "root", "", "Qgiv");
    // Check connection
    if ($connect->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    //handle mysql injection
?>

<!-----------Function for Date format----------------------------------------->
<?php
//function for translating the date
function dob_config($dobstr){
    $newstr = substr($dobstr, 0, -10);
    $numbers = explode('-', $newstr);
    switch ($numbers[1]) {
    case "01":
        $dobMonth = "January";
        break;
    case "02":
        $dobMonth = "February";
        break;
    case "03":
        $dobMonth = "March";
        break;
    case "04":
        $dobMonth = "April";
        break;
    case "05":
        $dobMonth = "May";
        break;
    case "06":
        $dobMonth = "June";
        break;
    case "07":
        $dobMonth = "July";
        break;
    case "08":
        $dobMonth = "August";
        break;
    case "09":
        $dobMonth = "September";
        break;
    case "10":
        $dobMonth = "October";
        break;
    case "11":
        $dobMonth = "November";
        break;
    case "12":
        $dobMonth = "December";
        break;
}
    $newstr = "{$dobMonth} {$numbers[1]}, {$numbers[0]}";
    return $newstr;
}
?>

<!DOCTYPE html>
<!--[if lt IE 7]> <html class="no-js lt-ie9 lt-ie8 lt-ie7" lang="en"> <![endif]-->
<!--[if IE 7]>    <html class="no-js lt-ie9 lt-ie8" lang="en"> <![endif]-->
<!--[if IE 8]>    <html class="no-js lt-ie9" lang="en"> <![endif]-->
<!--[if gt IE 8]><!--> <html class="no-js" lang="en"> <!--<![endif]-->

<!-----------------Head---------------------------------------------------------------------------->
<head>
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <meta name="viewport" content="width=device-width" />
    
    <title>Qgiv Engineering Exercise</title>
    
    <link rel="stylesheet" type="text/css" href="https://secure.qgiv.com/resources/admin/css/application.css" />

    <style type="text/css">
        .container{ max-width: 1200px; margin: 0 auto; }
        .logo-header{ padding: 2em; }
        .logo{ margin: 0 auto; min-height: 80px; }
    </style>
</head>

<body>
<style>
ul#input li {
  display:inline;
}
</style>

    <!-- Create Transaction Modal -------------------------------------------------------------------->
      <div class="modal fade" id="newTransactionModal" tabindex="-1" role="dialog" aria-hidden="true">
       <div class="modal-dialog" role="document">
          <div class="modal-content">

          <?php include('newTransaction_modal.php'); ?>
        </div>
      </div>
    </div>  

    <section class="container">
        <div class="logo-header">
            <img class="logo" src="https://secure.qgiv.com/resources/core/images/logo-qgiv.svg" alt="Qgiv logo" />
        </div>

        <!-- Buttons------------------------------------------------------------------------------------>
        <li class="nav justify-content-center">
            <button onclick="location.href='index.php'" type="button">Users</button>
            <button onclick="location.href='transactions.php'" type="button">Transactions</button>
      	</li>

        <div class="data-table-container">
            <table id = "myTable" class="data-table">

                <thead>
                    <tr>
                        <th onclick ="sortTable(0)" class="ui-secondary-color">ID</th>
                        <th onclick ="sortTable(1)" class="ui-secondary-color">Timestamp</th>
                        <th onclick ="sortTable(2)" class="ui-secondary-color">Amount</th>
                        <th onclick ="sortTable(3)" class="ui-secondary-color">Status</th>
                        <th onclick ="sortTable(4)" class="ui-secondary-color">Payment Type</th>
                        <th onclick ="sortTable(5)" class="ui-secondary-color">User Email</th>
                    </tr>
                </thead>
                <tbody>
                
                <?php

                if (isset($_GET['pageno'])) {
                $pageno = $_GET['pageno'];
                } else {
                    $pageno = 1;
                }
                $no_of_records_per_page = 20;
                $offset = ($pageno-1) * $no_of_records_per_page;

                $total_pages_sql = "SELECT COUNT(*) FROM transactions";
                $result = mysqli_query($connect,$total_pages_sql);
                $total_rows = mysqli_fetch_array($result)[0];
                $total_pages = ceil($total_rows / $no_of_records_per_page);

                $sql = "SELECT * FROM transactions LIMIT $offset, $no_of_records_per_page";
                $res_data = mysqli_query($connect,$sql);

                //query for user table--------------------------------------------------------------------------------------------------->
		        $msql = "SELECT idtransactions, amount, status, payment_type, user_email, timestamp FROM transactions";

		        $result = $connect->query($msql);
                
		        if ($result->num_rows > 0) {
   		        // output data of each row
    	            while($row = mysqli_fetch_array($res_data)){
                        echo "<tr>
                        <td>". $row["idtransactions"] . "</td>
                        <td>". $row["timestamp"] . "</td>
                        <td>". $row["amount"] . "</td>
                        <td>". $row["status"]. "</td>
                        <td>". $row["payment_type"]. "</td>
                        <td>". $row["user_email"]. "</td>
                        </tr>";
                        //<td><input class='myclass' type='button' value='Add Transaction'/></td>
    	            }
                }

    $connect->close();
	?>

                </tbody>
            </table>
        </div>
    </section>

<script>
function sortTable(n) {
  var table, rows, switching, i, x, y, shouldSwitch, dir, switchcount = 0;
  table = document.getElementById("myTable");
  switching = true;
  dir = "asc"; 
  while (switching) {
    switching = false;
    rows = table.rows;
    for (i = 1; i < (rows.length - 1); i++) {
      shouldSwitch = false;
      x = rows[i].getElementsByTagName("TD")[n];
      y = rows[i + 1].getElementsByTagName("TD")[n];
      if (dir == "asc") {
        if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
          shouldSwitch= true;
          break;
        }
      } else if (dir == "desc") {
        if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
          shouldSwitch = true;
          break;
        }
      }
    }
    if (shouldSwitch) {
      rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
      switching = true;
      switchcount ++;      
    } else {
      if (switchcount == 0 && dir == "asc") {
        dir = "desc";
        switching = true;
      }
    }
  }
}
</script>

<!------Pagination-------------->
<ul class="pagination">
        <li><a href="?pageno=1">First</a></li>
        <li class="<?php if($pageno <= 1){ echo 'disabled'; } ?>">
            <a href="<?php if($pageno <= 1){ echo '#'; } else { echo "?pageno=".($pageno - 1); } ?>">Prev</a>
        </li>
        <li class="<?php if($pageno >= $total_pages){ echo 'disabled'; } ?>">
            <a href="<?php if($pageno >= $total_pages){ echo '#'; } else { echo "?pageno=".($pageno + 1); } ?>">Next</a>
        </li>
        <li><a href="?pageno=<?php echo $total_pages; ?>">Last</a></li>
</ul>

</body>
</html>
