TGraphAsymmErrors* hist_to_graph(TH1F* hist, double left=-9999, double right=9999, bool drawyerror=false){

  TH1::SetDefaultSumw2(true);

  int bin_left(1), bin_right(hist->GetXaxis()->GetNbins());

  for(unsigned int i=1; i<=hist->GetXaxis()->GetNbins(); i++){
    if( hist->GetXaxis()->GetBinLowEdge(i) == left ) bin_left = i;
    if( hist->GetXaxis()->GetBinUpEdge(i) == right ) bin_right = i;
  }

  //cout << "bin_left = " << bin_left << ", bin_right = " << bin_right << endl;

  int Nbins = bin_right-bin_left+1;

  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];
  TAxis *xaxis = hist->GetXaxis();

  for(Int_t i=0; i<Nbins; i++){
    //cout << "  "<<i<<endl;
    x[i] = xaxis->GetBinCenter(i+bin_left);
    y[i] = hist->GetBinContent(i+bin_left);
    xlow[i] = xaxis->GetBinCenter(i+bin_left)-xaxis->GetBinLowEdge(i+bin_left);
    xup[i] = xaxis->GetBinUpEdge(i+bin_left)-xaxis->GetBinCenter(i+bin_left);
    if(drawyerror){
      ylow[i] = hist->GetBinError(i+bin_left);
      yup[i] = hist->GetBinError(i+bin_left);
    }
    else{
      ylow[i] = 0;
      yup[i] = 0;
    }
    //cout << "  x = " << x[i] << ", y = " << y[i] << ", x_low = " << xlow[i] << ", xup = " << xup[i] << ", ylow = " << ylow[i] << ", yup = " << yup[i] << endl;
  }
  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}


TGraphAsymmErrors* hist_to_graph(TGraphAsymmErrors* gr, double left=-9999, double right=9999, bool drawyerror=false){

  TH1::SetDefaultSumw2(true);

  int bin_left(0), bin_right(gr->GetN()-1);

  Double_t *original_x, *original_x_high, *original_x_low, *original_y, *original_y_high, *original_y_low;
  original_x = gr->GetX();
  original_x_high = gr->GetEXhigh();
  original_x_low = gr->GetEXlow();
  original_y = gr->GetY();
  original_y_high = gr->GetEYhigh();
  original_y_low = gr->GetEYlow();

  for(unsigned int i=0; i<gr->GetN(); i++){
    if( original_x[i]-original_x_low[i] == left ) bin_left = i;
    if( original_x[i]+original_x_high[i] == right ) bin_right = i;
  }

  //cout << "bin_left = " << bin_left << ", bin_right = " << bin_right << endl;

  int Nbins = bin_right-bin_left+1;
  //cout << "Nbins = " << Nbins << endl;

  double x[Nbins], y[Nbins], xlow[Nbins], xup[Nbins], ylow[Nbins], yup[Nbins];

  for(Int_t i=0; i<Nbins; i++){
    x[i] = original_x[i+bin_left];
    xlow[i] = original_x_low[i+bin_left];
    xup[i] = original_x_high[i+bin_left];
    y[i] = original_y[i+bin_left];
    if(drawyerror){
      ylow[i] = original_y_low[i+bin_left];
      yup[i] = original_y_high[i+bin_left];
    }
    else{
      ylow[i] = 0;
      yup[i] = 0;
    }

    //cout << "  x = " << x[i] << ", y = " << y[i] << ", x_low = " << xlow[i] << ", xup = " << xup[i] << ", ylow = " << ylow[i] << ", yup = " << yup[i] << endl;
  }

  TGraphAsymmErrors *out = new TGraphAsymmErrors(Nbins, x, y, xlow, xup, ylow, yup);
  out->SetTitle("");
  return out;

}
