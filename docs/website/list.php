<?php
// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2018
//
// LibLapin

if (!isset($doctype))
  exit(1);

$all_mods = "[ ";
foreach (scandir("$language/$doctype/") as $mod)
{
  if ($mod[0] != "." && strstr($mod, ".php") == false)
    $all_mods .= "'$mod',";
}
$all_mods[strlen($all_mods) - 1] = "]";

?>
<a onClick="roll_unroll_all(<?=$all_mods; ?>);" class="roll_button">
  <h3 class="button control_button"><?=$RollUnrollAll; ?></h3>
</a>

<ul class="prime_list">
<?php
foreach (scandir("$language/$doctype/") as $mod)
{
  if ($mod[0] != "." && strstr($mod, ".php") == false)
  {
?>
  <li class="button prime_list_item">
    <div class="prime_list_item">
      <a onClick="roll_unroll('<?=$mod; ?>');">
        <img id="<?=$mod; ?>_arrow" src="res/arrow_right.png" />
      </a>
      <a href="index.php?pag=4&amp;doc=<?=$doctype; ?>&amp;mod=<?=$mod; ?>">
        <h2><?=pretty_name($mod); ?></h2>
      </a>
    </div>
    <ul id="<?=$mod; ?>_sublist" class="second_list" style="display: none;">
    <?php
    $entries = [];
    foreach (scandir("$language/$doctype/$mod/") as $sym)
    {
      if ($sym[0] != "."
          && $sym[0] != "#"
          && $sym != "main.php"
          && $sym[strlen($sym) - 1] != "~")
      {
        $sym = str_replace(".php", "", $sym);
        $entries[] = skip_int_label($sym);
      }
    }
    foreach ($entries as $sym)
    {
    ?>
      <li>
        <a href="index.php?pag=4&amp;doc=<?=$doctype; ?>&amp;mod=<?=$mod; ?>#<?=base64_encode($sym); ?>">
          <h3 class="button second_list_entry"><?=$sym; ?></h3>
        </a>
      </li>
    <?php
    }
    ?>
    </ul>
  </li>
<?php
  }
}
?>
</ul>
