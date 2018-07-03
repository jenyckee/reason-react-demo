[%bs.raw {|require('./App.css')|}];
[@bs.module] external logo : string = "./logo.svg";

open Belt;

type action =
  | Tick
  | Double;

/* The component's state type. It can be anything, including, commonly, being a record type */
type state = {
  count: int, 
  values: list(int)
};

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {
    count: 0, 
    values: []
  },
  reducer: (action, state) =>
    switch (action) {
      | Tick => ReasonReact.Update({
        ...state,
        count: state.count + 1
      })
      | Double => ReasonReact.Update({
        count: state.count * 2, 
        values: [state.count, ...state.values]
      })
    },
  subscriptions: self => [
    Sub(
      () => Js.Global.setInterval(() => self.send(Tick), 1000),
      Js.Global.clearInterval,
    ),
  ],
  render: ({state, send}) =>
    <div className="App" onClick=((_) => send(Double))>
      /* <QrCode value="https://studiohyperdrive.be/"/> */
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.string(string_of_int(state.count))) </h2>
      </div>
      <ul>
        (
          /* The pipe |> is a left-associative binary operator that's defined as a |> b == b(a).  */
          Array.map(List.toArray(state.values), value =>
            <li>(ReasonReact.string(string_of_int(value)))</li>) |> ReasonReact.arrayToElement
        )
      </ul>
      <p className="App-intro">
        (ReasonReact.string("To get started, edit"))
        <code> (ReasonReact.string(" src/App.re ")) </code>
        (ReasonReact.string("and save to reload."))
      </p>
    </div>,
};
