<div class="prototype">
  $Ktypedef struct@ $Ts_bunny_astack@<br />
  {<br />
  $A $Kconst@ $Tsize_t@ $Slength@;<br />
  $A $Kconst@ $Tvoid@	* $Kconst@ * $Kconst@ $Stop@;<br />
  <br />
  } $Tt_bunny_astack@;<br />
</div>
<hr />

<div class="resume">
  <h3>Description</h3>
  $A This structure is the main data of the AStack container.
  <br />
  <br />
  $A This type cannot be declared on stack. It must be created by a call
  to bunny_new_astack.
</div>
<hr />

<div class="parameters">
  <h3>Attributes</h3>
  <ul>
    <li>
      $Kconst@ $Tsize_t@ $Slength@:<br />
      $A The amount of elements in the AStack container.
    </li>
    <li>
      $Kconst@ $Tvoid@	* $Kconst@ * $Kconst@ * $Stop@:<br />
      $A A pointer to a node containing the first element of the AStack container,
      and the address of its following element if there is one.
      This attribute is $CNULL@ if there is no element inside the AStack.
    </li>
  </ul>
</div>

