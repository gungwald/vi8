unit stryng;

interface

const
  STRYNG_MAX = 128;

type
  StryngSize = 0..STRYNG_MAX;
  Stryng = record
    len  : Stryng;
    data : packed array[1..STRYNG_MAX] of char;
  end;

procedure sInit(var s:Stryng);
begin
  s.len := 0;
end;
