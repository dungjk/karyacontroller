/*





  =========================

  #ifdef DRIVE_DELTA
  void addmoveDELTA(float cf, float cx2, float cy2 , float cz2, float ce02, int g0 , int rel)
  {
  // create delta segments if needed


  int32_t dist;

  // deltas
  dist = approx_distance(labs(cx2 - cx1), labs(cy2 - cy1)); //,labs(diff.axis[nZ]));
  if (dist < 2) {
    addmove(cf, cx2, cy2, cz2, ce02, g0, rel);
    return;
  }
  float df[4], cx[4];
  float sc = 1.0f / dist;
  df[0] = float(cx2 - cx1) * sc;
  df[1] = float(cy2 - cy1) * sc;
  df[2] = float(cz2 - cz1) * sc;
  df[3] = float(ce02 - ce01) * sc;



  int segment_total = dist;
  zprintf(PSTR("Dist:%d Segmen:%d\n"), fi(dist), fi(segment_total));

  if ((df[nX] == 0 && df[nY] == 0))
  {
    addmove(cf, cx2, cy2, cz2, ce02, g0, rel);
    return;
  } else {

    //if you do all segments, rounding error reduces total - error will accumulate
    for (int s = 1; s < segment_total; s++) {

      addmove(cf, cx1 + (s * df[0]), cy1 + (s * df[1]), cz1 + (s * df[2]), ce01 + (s * df[3]), g0, rel);
    }
    //last bit to make sure we end up at the unsegmented target
    //segment = *target;
    //addmove(cf,cx2,cy2,cz2,ce02,g0,rel);
  }

  }

  #endif




  uint32_t approx_distance_3(uint32_t dx, uint32_t dy, uint32_t dz) {
  uint32_t min, med, max, approx;

  if ( dx < dy ) {
    min = dy;
    med = dx;
  } else {
    min = dx;
    med = dy;
  }

  if ( dz < min ) {
    max = med;
    med = min;
    min = dz;
  } else if ( dz < med ) {
    max = med;
    med = dz;
  } else {
    max = dz;
  }

  approx = ( max * 860 ) + ( med * 851 ) + ( min * 520 );
  if ( max < ( med << 1 )) approx -= ( max * 294 );
  if ( max < ( min << 2 )) approx -= ( max * 113 );
  if ( med < ( min << 2 )) approx -= ( med *  40 );

  // add 512 for proper rounding
  return (( approx + 512 ) >> 10 );
  }
  uint32_t approx_distance(uint32_t dx, uint32_t dy) {
  uint32_t min, max, approx;

  // If either axis is zero, return the other one.
  if (dx == 0 || dy == 0) return dx + dy;

  if ( dx < dy ) {
    min = dx;
    max = dy;
  } else {
    min = dy;
    max = dx;
  }

  approx = ( max * 1007 ) + ( min * 441 );
  if ( max < ( min << 4 ))
    approx -= ( max * 40 );

  // add 512 for proper rounding
  return (( approx + 512 ) >> 10 );
  }




      Problems:
       we dont know exact step needed from start to end
       so, we need to change the ramping acceleration calculation

       my idea is to stretch, so make the rampup and rampdown as float, and decrease it using a floating number
       for linear system it decrease by 1, but for non linear, it will interpolate the decrease, so on segment calculation
       need to change the decreasing value

      totalseg=number segment
      int segno =-1 // for first calc become 0
      float sgx = deltax/stepmmx[fastaxis]
      float sgy = deltay/stepmmx[fastaxis]
      float sgz = deltaz/stepmmx[fastaxis]
      float sge = deltae/stepmmx[fastaxis]

      int mctr =0 (to trigger first calculation) stepmmx decreasing if reach zero reset to stepmmx ,segno ++
      LOOP
      if mctr<= 0 && totalseg>0
      {
        newx=segno++ * sgx + x[0]
        ...

        transformdelta newx,...
        deltax=newx-currentx
        ...
        // reset bresenham direction
        mtotalstep= biggest delta
        mcx[0]=totalstep/2

        currentx=newx
        ...

        segctr=stepmmx[fastaxis]
      } else {
      // segment bresenham



      }




  void prepareramp(int32_t bpos)
  {

  #define preprampdebug
  tmove *m, *next;
  m = &moves[bpos];
  //if (m->status & 4)return; // already calculated

  int faxis = FASTAXIS(m);
  int32_t ytotalstep = labs(m->dx[faxis]);
  #define stepmm  Cstepmmx(faxis)

  float stepa = stepmm / (m->ac);
  //float stepa = (ytotalstep*m->dis/m->ac); // *stepmm / (m->ac);
  //float stepa = m->axs*stepmm / (m->ac);
  float stepb = stepa;//stepmm / (m->ac);//(accel); // deceleration always use the feed accell
  CORELOOP
  if (bpos != (head)) {
    next = &moves[nextbuff(bpos)];
    fe = next->fs;
  } else fe = 0;
  rampup = rampdown = 0;
  ramplenq(rampup, m->fs, m->fn, stepa);
  ramplenq(rampdown, fe, m->fn, stepa);

  #ifdef preprampdebug
  zprintf(PSTR("\n========1========\nRU:%d Rd:%d Ts:%d\n"), rampup, rampdown, ytotalstep);
  zprintf(PSTR("FS:%f AC:%f FN:%f FE:%f\n"), ff(m->fs), ff(m->ac), ff(m->fn),  ff(fe));
  #endif

  if (rampup + rampdown > ytotalstep) {
    // if crossing and have rampup
    int32_t r = ((rampdown + rampup) - ytotalstep) / 2;
    rampup -= r;
    rampdown -= r;
    if (rampup < 0)rampup = 0;
    if (rampdown < 0)rampdown = 0;
    if (rampdown > ytotalstep)rampdown = ytotalstep;
    if (rampup > ytotalstep)rampup = ytotalstep;
    m->fn = speedat(m->fs, m->ac, rampup, stepmm);

    if (rampdown == 0)next->fs = m->fn;
  }

  CORELOOP

  #ifdef preprampdebug
  zprintf(PSTR("========FINAL========\nRU:%d Rd:%d\n"), rampup, rampdown);
  zprintf(PSTR("FS:%f AC:%f FN:%f FE:%f\n"), ff(m->fs), ff(m->ac), ff(m->fn),  ff(fe));
  #endif
  m->status |= 4;
  CORELOOP
  }


*/
