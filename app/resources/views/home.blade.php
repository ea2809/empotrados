@extends('layouts.app')

@section('content')
<div class="container">
    <div class="row">
        <div class="col-md-8 col-md-offset-2">
            <div class="panel panel-default">
                <div class="panel-heading">Códigos</div>

                <div class="panel-body">
                    @if($codigo)
                        Tienes códigos
                    @else
                        No tienes códigos
                    @endif
                </div>
            </div>
        </div>
    </div>
</div>
@endsection
