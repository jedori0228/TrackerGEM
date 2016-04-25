#include "GE11.C"
#include "GE21.C"
#include "draw.C"

void run(){
  GE11 ge11_MuonGun("./rootfiles/histogram_MuonGun.root");
  GE21 ge21_MuonGun("./rootfiles/histogram_MuonGun.root");

  ge11_MuonGun.outputfile_name = "./plots/GE11_MuonGun.root";
  ge21_MuonGun.outputfile_name = "./plots/GE21_MuonGun.root";
  ge11_MuonGun.Loop();
  ge21_MuonGun.Loop();

  GE11 ge11_MinBias("./rootfiles/histogram_MinBias.root");
  GE21 ge21_MinBias("./rootfiles/histogram_MinBias.root");

  ge11_MinBias.outputfile_name = "./plots/GE11_MinBias.root";
  ge21_MinBias.outputfile_name = "./plots/GE21_MinBias.root";
  ge11_MinBias.Loop();
  ge21_MinBias.Loop();

  draw();
}
