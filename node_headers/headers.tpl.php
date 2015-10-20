<ul>
  <?php foreach ($items as $item): ?>
    <li> <?php print $item; ?> </li>
  <?php endforeach; ?>
</ul>

<?php foreach ($groups as $name => $group): ?>
  <?php print "<${name}> ${name} </${name}>"; ?>
  <ul>
    <?php foreach ($group as $item): ?>
      <li> <?php print $item; ?> </li>
    <?php endforeach; ?>
  </ul>
<?php endforeach; ?>
