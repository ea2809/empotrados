@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row">
        <div class="col-md-8 col-md-offset-2">
            <div class="panel panel-default">
                <div class="panel-heading">Códigos</div>

                <div class="panel-body">
                    @if($codigo)
                        Tu código es <strong>{{ $codigo->code }}</strong><br><br>
                        <a href="/generar" class="btn btn-primary">Re-generar</a>
                    @else
                        No tienes códigos<br><br>
                        <a href="/generar" class="btn btn-primary">Generar</a>
                    @endif
                </div>
            </div>
        </div>
    </div>
</div>
@endsection
