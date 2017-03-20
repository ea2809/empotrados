<?php

namespace App\Http\Controllers;

use App\Codigo;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;
class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Show the application dashboard.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $data = [];
        $data['codigo'] = Auth::user()->codigo;
        return view('home', $data);
    }

    public function generar()
    {
        $user = Auth::user();
        $codigo = $user->codigo;
        if (! $codigo)
            $codigo = new Codigo();

        $codigo->code = $this->generarCodigo();
        $codigo->user_id = $user->id;
        $guardado = $codigo->save();

        // Si falla seguimos intentando
        if(! $guardado)
            return $this->generar();

        return redirect('/home');
    }

    private function generarCodigo()
    {
        $min=1;
        $max=9999;
        return $this->pasarAstring(rand($min,$max));
    }

    private function pasarAstring($rand)
    {
        if($rand < 10)
            return "000" . $rand;

        if($rand < 100)
            return "00" . $rand;

        if($rand < 1000)
            return "0" . $rand;

        return "". $rand;
    }

}
