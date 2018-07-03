[@bs.module] external qrCode : ReasonReact.reactClass = "qrcode.react";

[@bs.deriving abstract]
type jsProps = {
  value: string
};

/* This is like declaring a normal ReasonReact component's `make` function, except the body is a the interop hook wrapJsForReason */
let make = (~value, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass=qrCode,
    ~props=jsProps(~value),
    children,
  );