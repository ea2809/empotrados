<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class CodigosController extends Controller
{
    public function check($id, $code)
    {
        // Por ahora sin id
        $codes = Codigo::where('code', $code)->get();
        if($codes->isEmpty()) {
            // TODO: no existe
            return "0";
        } else if ($codes->count() == 1) {
            $codigo = $codes->first();
            $this->generador($codigo->user);
            return "1";
        } else {
            // TODO: Algo ha pasado, hay más de uno;
            return "2";
        }

    }

    private function generador($user)
    {

        $codigo = $user->codigo;
        if (!$codigo)
            $codigo = new Codigo();

        $codigo->code = $this->generarCodigo();
        $codigo->user_id = $user->id;
        $guardado = $codigo->save();

        // Si falla seguimos intentando
        if (!$guardado)
            return $this->generador($user);

        return $guardado;
    }

    private function generarCodigo()
    {
        $min = 1;
        $max = 9999;
        return $this->pasarAstring(rand($min, $max));
    }

    private function pasarAstring($rand)
    {
        if ($rand < 10)
            return "000" . $rand;

        if ($rand < 100)
            return "00" . $rand;

        if ($rand < 1000)
            return "0" . $rand;

        return "" . $rand;
    }
}
