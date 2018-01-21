<div class="prototype">
  $Tbool@ $Sbunny_circle_collision_dot@(
  $Kconst@ $Tt_bunny_accurate_position@ *$Scircle_coord@,
  $Kconst@ $Tt_bunny_accurate_position@ *$Sdot@,
  $Tdouble@ $Sradius@
  );
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A Test the collision a circle at position $Scircle_coord@ of radius $Sradius@
  with $Sdot@.
</div>
<hr />

<div class="parameters">
  <h3>Parameters</h3>
  <ul>
    <li>
      $Kconst@ $Tt_bunny_accurate_position@ *@Scircle_coord@:
      $A Coordinates of the circle to collide with $Sdot@.
    </li>
    <li>
      $Kconst@ $Tt_bunny_accurate_position@ *$Sdot@:
      $A The coordinates of the dot to collide with the circle.
    </li>
    <li>
      $Tdouble@ $Sradius@:
      $A The radius of the circle.
    </li>
  </ul>
</div>
<hr />

<div class="return">
  <h3>Return value</h3>
  <p>
    $Ctrue@ or $Cfalse@ depending if there is a collision or not.
  </p>
</div>
<hr />

<div class="details">
  <h3>Additional informations</h3>
  <p>
    This function is part of the first version of the collide module
    and can be quite handy for simple program, but for more complex
    ones, consider using the bunny_collide system.
  </P>
</div>

