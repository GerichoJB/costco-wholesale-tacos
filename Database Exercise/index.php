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

                <h1>New Transaction</h1>

                <form action="insert.php" method="post">
                <ul id="input">
                <li>Amount: <input type="text" name="amount" /></li>
                <li>Status: <input type="text" name="status" /></li>
                <li>Type: <input type="text" name="payment_type" /></li>
                <li>Email: <input type="text" name="user_email" /></li>
                <input type="submit" />
                </ul>
                </form>
                <thead>
                    <tr>
                        <th onclick ="sortTable(0)" class="ui-secondary-color">Name</th>
                        <th onclick ="sortTable(1)" class="ui-secondary-color">Address</th>
                        <th onclick ="sortTable(2)" class="ui-secondary-color">Email</th>
                        <th onclick ="sortTable(3)" class="ui-secondary-color">DOB</th>
                        <th class="ui-secondary-color">Image</th>
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

                $total_pages_sql = "SELECT COUNT(*) FROM users";
                $result = mysqli_query($connect,$total_pages_sql);
                $total_rows = mysqli_fetch_array($result)[0];
                $total_pages = ceil($total_rows / $no_of_records_per_page);

                $sql = "SELECT * FROM users LIMIT $offset, $no_of_records_per_page";
                $res_data = mysqli_query($connect,$sql);

                //query for user table--------------------------------------------------------------------------------------------------->
		        $msql = "SELECT CONCAT(results_name_first, ' ', results_name_last) as Name, CONCAT(results_location_street, ' ', results_location_city, ' ', results_location_state, ' ', results_location_postcode) as Address, results_email, results_dob_date, results_picture_thumbnail FROM users";

		        $result = $connect->query($msql);
                
		        if ($result->num_rows > 0) {
   		        // output data of each row
    	            while($row = mysqli_fetch_array($res_data)){
                        $image = $row["results_picture_thumbnail"];
                        $imageData = base64_encode(file_get_contents($image));
                        echo "<tr><td><a class='' href='userDetails_page.php?results_email=".$row["results_email"]."'>" . ucwords($row["results_name_first"]) . ' '. ucwords($row["results_name_last"]) . "</td>
                        <td>". ucwords($row["results_location_street"]). ', ' . ucwords($row["results_location_city"]). ', '. ucwords($row["results_location_state"]). ' '. $row["results_location_postcode"]. "</td>
                        <td>". $row["results_email"]. "</td>
                        <td>". dob_config($row["results_dob_date"]). "</td>
                        <td>". '<img src="data:image/jpeg;base64,'.$imageData.'">'; "</td>
                        </tr>";
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
  //Set the sorting direction to ascending:
  dir = "asc"; 
  /*Make a loop that will continue until
  no switching has been done:*/
  while (switching) {
    //start by saying: no switching is done:
    switching = false;
    rows = table.rows;
    /*Loop through all table rows (except the
    first, which contains table headers):*/
    for (i = 1; i < (rows.length - 1); i++) {
      //start by saying there should be no switching:
      shouldSwitch = false;
      /*Get the two elements you want to compare,
      one from current row and one from the next:*/
      x = rows[i].getElementsByTagName("TD")[n];
      y = rows[i + 1].getElementsByTagName("TD")[n];
      /*check if the two rows should switch place,
      based on the direction, asc or desc:*/
      if (dir == "asc") {
        if (x.innerHTML.toLowerCase() > y.innerHTML.toLowerCase()) {
          //if so, mark as a switch and break the loop:
          shouldSwitch= true;
          break;
        }
      } else if (dir == "desc") {
        if (x.innerHTML.toLowerCase() < y.innerHTML.toLowerCase()) {
          //if so, mark as a switch and break the loop:
          shouldSwitch = true;
          break;
        }
      }
    }
    if (shouldSwitch) {
      /*If a switch has been marked, make the switch
      and mark that a switch has been done:*/
      rows[i].parentNode.insertBefore(rows[i + 1], rows[i]);
      switching = true;
      //Each time a switch is done, increase this count by 1:
      switchcount ++;      
    } else {
      /*If no switching has been done AND the direction is "asc",
      set the direction to "desc" and run the while loop again.*/
      if (switchcount == 0 && dir == "asc") {
        dir = "desc";
        switching = true;
      }
    }
  }
}
</script>

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
