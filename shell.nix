{ pkgs ? import <nixpkgs> { }
}:
pkgs.mkShell {
  name = "qmk-firmware";

  buildInputs = with pkgs; [
    clang-tools
    (qmk.override { python3 = python313; })
  ];
}
