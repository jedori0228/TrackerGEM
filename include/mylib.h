TGraphAsymmErrors* hist_to_graph(TH1F* hist){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins();
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=0; i<Nbins; i++){
    x[i] = xaxis->GetBinCenter(i+1);
    y[i] = hist->GetBinContent(i+1);
    xlow[i] = xaxis->GetBinCenter(i+1)-xaxis->GetBinLowEdge(i+1);
    xup[i] = xaxis->GetBinUpEdge(i+1)-xaxis->GetBinCenter(i+1);
    //ylow[i] = hist->GetBinError(i+1);
    //yup[i] = hist->GetBinError(i+1);
    ylow[i] = 0;
    yup[i] = 0;
    //cout << "x = " << x[i] << ", y = " << y[i] << ", x_low = " << xlow[i] << ", xup = " << xup[i] << ", ylow = " << ylow[i] << ", yup = " << yup[i] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  return out;

}

//==== special function for eta fake plot..
//==== removing 1.5 eta bin..
TGraphAsymmErrors* hist_to_graph(TH1F* hist, bool remove_first){

  TH1::SetDefaultSumw2(true);

  int Nbins = hist->GetXaxis()->GetNbins();
  if(remove_first) Nbins = Nbins-1;
  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();
  for(Int_t i=0; i<Nbins; i++){
    x[i] = xaxis->GetBinCenter(i+2);
    y[i] = hist->GetBinContent(i+2);
    xlow[i] = xaxis->GetBinCenter(i+2)-xaxis->GetBinLowEdge(i+2);
    xup[i] = xaxis->GetBinUpEdge(i+2)-xaxis->GetBinCenter(i+2);
    //ylow[i] = hist->GetBinError(i+1);
    //yup[i] = hist->GetBinError(i+1);
    ylow[i] = 0;
    yup[i] = 0;
    //cout << "x = " << x[i] << ", y = " << y[i] << ", x_low = " << xlow[i] << ", xup = " << xup[i] << ", ylow = " << ylow[i] << ", yup = " << yup[i] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  return out;

}
